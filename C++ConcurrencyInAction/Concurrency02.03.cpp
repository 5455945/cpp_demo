#include "Concurrency02.h"
#include <thread>
#include <iostream>
namespace C0203{
    // 使用RAII等待线程完成
    class thread_guard
    {
        std::thread& t;
    public:
        explicit thread_guard(std::thread& t_) :
            t(t_)
        {}
        ~thread_guard()
        {
            if (t.joinable())
            {
                t.join();
            }
        }
    private:
        thread_guard(thread_guard const&) = delete;
        thread_guard& operator=(thread_guard const&) = delete;
    };

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
        thread_guard g(t);
        std::cout << std::endl;
        std::cout << "02.03: " << some_local_state << std::endl;
        do_something_in_current_thread();
    }
}
void Concurrency02_03() {
    C0203::f();
    // Run-Time Check Failure #2 - Stack around the variable 'my_func' was corrupted.
}
