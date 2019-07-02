#include "Concurrency03.h"
#include <mutex>
// 3.2.5 避免死锁的进一步指南
// 1 避免嵌套锁(如果已经持有锁，就不要再获取锁)
// 2 在持有锁时，避免调用用户提供的代码
// 3 以固定顺序获取锁
// 4 使用锁层次
// 5 将这些设计准则扩展到锁之外
namespace {
    // 使用锁层次来避免死锁
    //class hierarchical_mutex
    //{
    //public:
    //    explicit hierarchical_mutex(unsigned level)
    //    {}
    //    // 实现必须的lock/unlock接口
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
    // 初始化 类静态本地线程变量
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
