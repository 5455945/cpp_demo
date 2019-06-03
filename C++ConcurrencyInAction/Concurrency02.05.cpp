#include "Concurrency02.h"
#include <thread>
namespace {
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