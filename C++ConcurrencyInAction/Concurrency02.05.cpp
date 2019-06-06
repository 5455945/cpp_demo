#include "Concurrency02.h"
#include <thread>
// 2.2 传递参数给线程函数
// 2.3 转移线程的所有权
namespace {
    // 从函数中返回std::thread
    void some_function()
    {}

    void some_other_function(int)
    {}

    std::thread f()
    {
        void some_function();
        return std::thread(some_function);
    }
    std::thread g()
    {
        void some_other_function(int);
        std::thread t(some_other_function, 42);
        return t;
    }
}
void Concurrency02_05() {
    std::thread t1 = f();
    t1.join();
    std::thread t2 = g();
    t2.join();
}