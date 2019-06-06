#include "Concurrency09.h" 
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <future>
// 9.2.4 中断在condition_variable_any上的等待
namespace {
    // 为std::condition_variable_any而设的interruptible_wait
    class interrupt_flag;
    extern thread_local interrupt_flag this_thread_interrupt_flag;
    class interrupt_flag
    {
        std::atomic<bool> flag;
        std::condition_variable* thread_cond;
        std::condition_variable_any* thread_cond_any;
        std::mutex set_clear_mutex;

    public:
        interrupt_flag() :
            flag(false), thread_cond(0), thread_cond_any(0)
        {}

        void set()
        {
            flag.store(true, std::memory_order_relaxed);
            std::lock_guard<std::mutex> lk(set_clear_mutex);
            if (thread_cond)
            {
                thread_cond->notify_all();
            }
            else if (thread_cond_any)
            {
                thread_cond_any->notify_all();
            }
        }

        bool is_set() const
        {
            return flag.load(std::memory_order_relaxed);
        }

        void interruption_point() {
            if (is_set())
            {
                throw std::logic_error("thread_interrupted()");
            }
        }

        template<typename Lockable>
        void wait(std::condition_variable_any& cv, Lockable& lk)
        {
            struct custom_lock
            {
                interrupt_flag* self;
                Lockable& lk;

                custom_lock(interrupt_flag* self_,
                    std::condition_variable_any& cond,
                    Lockable& lk_) :
                    self(self_), lk(lk_)
                {
                    self->set_clear_mutex.lock();
                    self->thread_cond_any = &cond;
                }

                void unlock()
                {
                    lk.unlock();
                    self->set_clear_mutex.unlock();
                }

                void lock()
                {
                    std::lock(self->set_clear_mutex, lk);
                }

                ~custom_lock()
                {
                    self->thread_cond_any = 0;
                    self->set_clear_mutex.unlock();
                }
            };

            custom_lock cl(this, cv, lk);
            interruption_point();
            cv.wait(cl);
            interruption_point();
        }
        // rest as before
    };
    thread_local interrupt_flag this_thread_interrupt_flag;

    template<typename Lockable>
    void interruptible_wait(std::condition_variable_any& cv,
        Lockable& lk)
    {
        this_thread_interrupt_flag.wait(cv, lk);
    }

    // 9.2.5 中断其它阻塞调用
    template <typename T>
    void interruptible_wait(std::future<T>& uf) {
        while (!this_thread_interrupt_flag.is_set()) {
            if (uf.wait_for(lk, std::chrono::milliseconds(1)) ==
                std::future_status::ready) {
                break;
            }
        }
        interruption_point();
    }
    // 9.2.6 处理中断
}
#include <iostream>
void Concurrency09_12() {
    std::cout << __FUNCTION__ << std::endl;
    std::condition_variable_any cv;
    std::thread t1([&]() {
        std::mutex m;
        std::unique_lock<std::mutex> lk(m);
        std::cout << __FUNCTION__ << " start" << std::endl;
        interruptible_wait<std::unique_lock<std::mutex>>(cv, lk);
        std::cout << __FUNCTION__ << " end" << std::endl;
        });
    std::thread t2([&]() {
        std::cout << __FUNCTION__ << " start" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        cv.notify_all();
        std::cout << __FUNCTION__ << " end" << std::endl;
        });
    t1.join();
    t2.join();
}