#include "Concurrency03.h"
#include <mutex>
// 3.2.5 ���������Ľ�һ��ָ��
// 1 ����Ƕ����(����Ѿ����������Ͳ�Ҫ�ٻ�ȡ��)
// 2 �ڳ�����ʱ����������û��ṩ�Ĵ���
// 3 �Թ̶�˳���ȡ��
// 4 ʹ�������
// 5 ����Щ���׼����չ����֮��
namespace {
    // ʹ�����������������
    //class hierarchical_mutex
    //{
    //public:
    //    explicit hierarchical_mutex(unsigned level)
    //    {}
    //    // ʵ�ֱ����lock/unlock�ӿ�
    //    void lock()
    //    {}
    //    void unlock()
    //    {}
    //};
    class hierarchical_mutex {
    private:

        std::mutex internal_mutex;

        unsigned long const hierarchy_value;
        unsigned long previous_hierarchy_value;

        // thread_local
        static thread_local unsigned long this_thread_hierarchy_value;
        void check_for_hierarchy_violation() {
            if (this_thread_hierarchy_value <= hierarchy_value)
                throw std::logic_error("mutex hierarchy violated");
        }

        void updata_hierarchy_value() {
            previous_hierarchy_value = this_thread_hierarchy_value;
            this_thread_hierarchy_value = hierarchy_value;
        }

    public:

        explicit hierarchical_mutex(unsigned long value) :
            hierarchy_value(value),
            previous_hierarchy_value(0)
        {}

        void lock() {
            check_for_hierarchy_violation();
            internal_mutex.lock();
            updata_hierarchy_value();
        }

        void unlock() {
            this_thread_hierarchy_value = previous_hierarchy_value;
            internal_mutex.unlock();
        }

        bool try_lock() {
            check_for_hierarchy_violation();
            if (!internal_mutex.try_lock()) {
                return false;
            }
            updata_hierarchy_value();
            return true;
        }
    };
    // ��ʼ�� �ྲ̬�����̱߳���
    thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX);

    hierarchical_mutex high_level_mutex(10000);
    hierarchical_mutex low_level_mutex(5000);

    int do_low_level_stuff()
    {
        return 42;
    }


    int low_level_func()
    {
        std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
        return do_low_level_stuff();
    }

    void high_level_stuff(int some_param)
    {}


    void high_level_func()
    {
        std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
        high_level_stuff(low_level_func());
    }

    void thread_a()
    {
        high_level_func();
    }

    hierarchical_mutex other_mutex(100);
    void do_other_stuff()
    {}


    void other_stuff()
    {
        high_level_func();
        do_other_stuff();
    }

    void thread_b()
    {
        std::lock_guard<hierarchical_mutex> lk(other_mutex);
        other_stuff();
    }
}
void Concurrency03_07() {
    other_stuff();
}
