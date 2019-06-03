#include "Concurrency03.h"
#include <memory>
#include <mutex>
// 3.3 用于共享数据保护的替代工具
// 3.3.1 在初始化时保护共享数据
namespace {
    struct some_resource
    {
        void do_something()
        {}
    };
    std::shared_ptr<some_resource> resource_ptr;
    std::mutex resource_mutex;
    void foo()
    {
        std::unique_lock<std::mutex> lk(resource_mutex); // 所有的线程在这里被序列化
        if (!resource_ptr)
        {
            resource_ptr.reset(new some_resource); // 只有初始化需要被保护
        }
        lk.unlock();
        resource_ptr->do_something();
    }
}
void Concurrency03_11() {
    foo();
}
