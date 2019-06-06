#include "Concurrency09.h"
#include <atomic>
#include <future>
#include <thread>
namespace {
    class interrupt_flag
    {
    private:
        std::atomic<bool> flag;
        std::condition_variable* thread_cond;
        std::mutex set_clear_mutex;
    public:
        interrupt_flag() :
            flag(false), thread_cond(0)
        {}
        void set()
        {
            flag.store(true, std::memory_order_relaxed);
            std::lock_guard<std::mutex> lk(set_clear_mutex);
            if (thread_cond)
            {
                thread_cond->notify_all();
            }
        }

        bool is_set() const
        {
            return flag.load(std::memory_order_relaxed);
        }
    };

    thread_local interrupt_flag this_thread_interrupt_flag;

    class interruptible_thread
    {
        std::thread internal_thread;
        interrupt_flag* flag;
    public:
        void join() {
            if (internal_thread.joinable()) {
                internal_thread.join();
            }
        }
        void detach() {
            if (internal_thread.joinable()) {
                internal_thread.detach();
            }
        }
        bool joinable() const {
            internal_thread.joinable();
        }

        template<typename FunctionType>
        interruptible_thread(FunctionType f)
        {
            std::promise<interrupt_flag*> p;
            internal_thread = std::thread([f, &p] {
                p.set_value(&this_thread_interrupt_flag);
                f();
                });
            internal_thread.join();
            flag = p.get_future().get();
        }

        void interrupt()
        {
            if (flag)
            {
                flag->set();
            }
        }
    };
}
#include <iostream>
void Concurrency09_09() {
    std::cout << __FUNCTION__ << std::endl;
    interruptible_thread it([]() { std::cout << __FUNCTION__ << std::endl; });
}