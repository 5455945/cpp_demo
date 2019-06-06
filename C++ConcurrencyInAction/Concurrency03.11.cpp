#include "Concurrency03.h"
#include <memory>
#include <mutex>
// 3.3 ���ڹ������ݱ������������
// 3.3.1 �ڳ�ʼ��ʱ������������
namespace {
    // ʹ�û���Ԫ�����̰߳�ȫ���ӳٳ�ʼ��
    struct some_resource
    {
        void do_something()
        {}
    };
    std::shared_ptr<some_resource> resource_ptr;
    std::mutex resource_mutex;
    void foo()
    {
        std::unique_lock<std::mutex> lk(resource_mutex); // ���е��߳������ﱻ���л�
        if (!resource_ptr)
        {
            resource_ptr.reset(new some_resource); // ֻ�г�ʼ����Ҫ������
        }
        lk.unlock();
        resource_ptr->do_something();
    }

    //// ���μ������(Double-Checked Locking),����ȡ���÷�
    //void underined_behaviour_with_double_checked_locking() {
    //    if (!resource_ptr) {
    //        std::lock_guard<std::mutex> lk(resource_mutex);
    //        if (!resource_ptr) {
    //            resource_ptr.reset(new some_resource);
    //        }
    //    }
    //    resource_ptr->do_something();
    //}
}
void Concurrency03_11() {
    foo();
}
