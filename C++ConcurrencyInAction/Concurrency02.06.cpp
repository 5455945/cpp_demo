#include "Concurrency02.h"
#include <thread>
//#include <utility>
#include <stdexcept>
namespace {
    // scoped_thread和示例用法
    class scoped_thread
    {
        std::thread t;
    public:
        explicit scoped_thread(std::thread t_) :
            t(std::move(t_))
        {
            if (!t.joinable())
                throw std::logic_error("No thread");
        }
        ~scoped_thread()
        {
            t.join();
        }
        scoped_thread(scoped_thread const&) = delete;
        scoped_thread& operator=(scoped_thread const&) = delete;
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
        scoped_thread t(std::thread(func(some_local_state)));
        do_something_in_current_thread();
    }
}
void Concurrency02_06() {
    f();
}