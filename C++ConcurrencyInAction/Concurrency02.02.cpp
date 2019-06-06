#include "Concurrency02.h"
#include <thread>
// 2.1.2 等待线程完成
// join(),joinable()
// 2.1.3 在异常环境下等待
namespace C0202{
    // 等待线程结束
    void do_something(int& i)
    {
        ++i;
    }

    struct func
    {
        int& i;

        func(int& i_) :i(i_) {}

        void operator()()
        {
            for (unsigned j = 0; j < 1000000; ++j)
            {
                do_something(i);
            }
        }
    };

    void do_something_in_current_thread()
    {}

    void f()
    {
        int some_local_state = 0;
        func my_func(some_local_state);
        std::thread t(my_func);
        try
        {
            do_something_in_current_thread();
        }
        catch (...)
        {
            t.join();
            throw;
        }
        t.join();
    }
}
void Concurrency02_02() {
    C0202::f();
}