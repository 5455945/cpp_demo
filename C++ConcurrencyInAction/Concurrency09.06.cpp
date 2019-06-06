#include "Concurrency09.h" 
#include <future>
#include <atomic>
#include <thread>
#include <queue>
#include <memory>
// 9.1.4 避免工作队列上的竞争
namespace {
    // 使用本地线程工作队列的线程池
    class thread_pool
    {
        std::atomic_bool done;
        threadsafe_queue<function_wrapper> pool_work_queue;
        std::vector<std::thread> threads;
        join_threads joiner;

        typedef std::queue<function_wrapper> local_queue_type;
        static thread_local std::unique_ptr<local_queue_type> local_work_queue;

        void worker_thread()
        {
            local_work_queue.reset(new local_queue_type);

            while (!done)
            {
                run_pending_task();
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

            std::packaged_task<result_type()> task(f);
            std::future<result_type> res(task.get_future());
            if (local_work_queue)
            {
                local_work_queue->push(std::move(task));
            }
            else
            {
                pool_work_queue.push(std::move(task));
            }
            return res;
        }

        void run_pending_task()
        {
            function_wrapper task;
            if (local_work_queue && !local_work_queue->empty())
            {
                task = std::move(local_work_queue->front());
                local_work_queue->pop();
                task();
            }
            else if (pool_work_queue.try_pop(task))
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
    thread_local std::unique_ptr<thread_pool::local_queue_type> thread_pool::local_work_queue = nullptr;
}
#include <iostream>
void Concurrency09_06() {
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