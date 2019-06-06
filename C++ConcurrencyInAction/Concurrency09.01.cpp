#include "Concurrency09.h" 
#include <thread>
#include <vector>
#include <atomic>
// 9 高级线性管理
// 9.1 线程池
// 9.1.1 最简单的线程池
namespace {
    // 简单线程池
    class thread_pool
    {
        std::atomic_bool done;
        threadsafe_queue<std::function<void()> > work_queue;
        std::vector<std::thread> threads;
        join_threads joiner;

        void worker_thread()
        {
            while (!done)
            {
                std::function<void()> task;
                if (work_queue.try_pop(task))
                {
                    task();
                }
                else
                {
                    std::this_thread::yield();
                }
            }
        }
    public:
        thread_pool() :
            done(false), joiner(threads)
        {
            unsigned const thread_count = std::thread::hardware_concurrency();
            try
            {
                for (unsigned i = 0; i < thread_count; ++i)
                {
                    threads.push_back(
                        std::thread(&thread_pool::worker_thread, this));
                }
            }
            catch (...)
            {
                done = true;
                throw;
            }
        }

        ~thread_pool()
        {
            done = true;
        }

        template<typename FunctionType>
        void submit(FunctionType f)
        {
            work_queue.push(std::function<void()>(f));
        }
    };
}
#include <iostream>
void test_run() {
    std::cout << __FUNCTION__ << std::endl;
}
void Concurrency09_01() {
    std::cout << __FUNCTION__ << std::endl;
    thread_pool tp;
    tp.submit(test_run);
    tp.submit([]() { std::cout << "lambda 09.01" << std::endl; });
    tp.submit([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "sleep_for(100 ms)" << std::endl;
        });
}