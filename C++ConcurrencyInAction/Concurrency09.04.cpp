#include "Concurrency09.h" 
#include <deque>
#include <future>
#include <memory>
#include <functional>
#include <iostream>
#include <iostream>
namespace {
    // run_pending_task()的实现
    class thread_pool
    {
    private:
        std::atomic_bool done;
        threadsafe_queue<function_wrapper> work_queue;
        std::vector<std::thread> threads;
        join_threads joiner;

        void worker_thread() {
            while (!done) {
                function_wrapper task;
                if (work_queue.try_pop(task)) {
                    task();
                }
                else {
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
        std::future<typename std::result_of<FunctionType()>::type>
            submit(FunctionType f)
        {
            typedef typename std::result_of<FunctionType()>::type result_type;

            std::packaged_task<result_type()> task(std::move(f));
            std::future<result_type> res(task.get_future());
            work_queue.push(std::move(task));
            return res;
        }

        // run_pending_task()的实现
        void run_pending_task()
        {
            function_wrapper task;
            if (work_queue.try_pop(task))
            {
                task();
            }
            else
            {
                std::this_thread::yield();
            }
        }
        // rest as before
    };
}
void Concurrency09_04() {
    std::cout << __FUNCTION__ << std::endl;
    thread_pool tp;
    tp.submit([]() {std::cout << __FUNCTION__ << std::endl; });
    tp.submit([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "sleep_for(100 ms)" << std::endl;
        });
    // 如果不调用，会在析构时被调用
    tp.run_pending_task();
    tp.run_pending_task();
}