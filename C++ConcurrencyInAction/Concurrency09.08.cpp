#include "Concurrency09.h" 
#include <atomic>
#include <future>
#include <thread>
#include <vector>
#include <queue>
#include <memory>
namespace {
    // 使用工作窃取的线程池
    class work_stealing_queue
    {
    private:
        typedef function_wrapper data_type;
        std::deque<data_type> the_queue;
        mutable std::mutex the_mutex;

    public:
        work_stealing_queue()
        {}

        work_stealing_queue(const work_stealing_queue& other) = delete;
        work_stealing_queue& operator=(
            const work_stealing_queue& other) = delete;

        void push(data_type data)
        {
            std::lock_guard<std::mutex> lock(the_mutex);
            the_queue.push_front(std::move(data));
        }

        bool empty() const
        {
            std::lock_guard<std::mutex> lock(the_mutex);
            return the_queue.empty();
        }

        bool try_pop(data_type& res)
        {
            std::lock_guard<std::mutex> lock(the_mutex);
            if (the_queue.empty())
            {
                return false;
            }

            res = std::move(the_queue.front());
            the_queue.pop_front();
            return true;
        }

        bool try_steal(data_type& res)
        {
            std::lock_guard<std::mutex> lock(the_mutex);
            if (the_queue.empty())
            {
                return false;
            }

            res = std::move(the_queue.back());
            the_queue.pop_back();
            return true;
        }
    };
    class thread_pool
    {
        typedef function_wrapper task_type;

        std::atomic_bool done;
        threadsafe_queue<task_type> pool_work_queue;
        std::vector<std::unique_ptr<work_stealing_queue>> queues;
        std::vector<std::thread> threads;
        join_threads joiner;

        static thread_local work_stealing_queue* local_work_queue;
        static thread_local unsigned my_index;

        void worker_thread(unsigned my_index_)
        {
            my_index = my_index_;
            local_work_queue = queues[my_index].get();
            while (!done)
            {
                run_pending_task();
            }
        }

        bool pop_task_from_local_queue(task_type& task)
        {
            return local_work_queue && local_work_queue->try_pop(task);
        }

        bool pop_task_from_pool_queue(task_type& task)
        {
            return pool_work_queue.try_pop(task);
        }

        bool pop_task_from_other_thread_queue(task_type& task)
        {
            for (unsigned i = 0; (i < queues.size()) && (i != my_index); ++i)
            {
                //unsigned const index = (my_index + i + 1) % queues.size();
                if (queues[i]->try_steal(task))
                {
                    return true;
                }
            }
            return false;
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
                    queues.push_back(std::unique_ptr<work_stealing_queue>(
                        new work_stealing_queue));
                    threads.push_back(
                        std::thread(&thread_pool::worker_thread, this, i));
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
        std::future <typename std::result_of<FunctionType()>::type> submit(
            FunctionType f)
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
            task_type task;
            if (pop_task_from_local_queue(task)) {
                task();
            }
            else if (pop_task_from_pool_queue(task)) {
                task();
            //} else if (pop_task_from_other_thread_queue(task)) {
            //    // 从其它线程窃取不太可取，应该在分配的时候控制比较好；窃取控制比较复杂
            //    task();
            }
            else
            {
                std::this_thread::yield();
            }
        }
    };
    thread_local work_stealing_queue* thread_pool::local_work_queue = nullptr;
    thread_local unsigned thread_pool::my_index = 0;
}
#include <iostream>
#include <list>
void Concurrency09_08() {
    std::cout << __FUNCTION__ << std::endl;
    thread_pool tp;
    tp.submit([]() {std::cout << __FUNCTION__ << std::endl; });
    tp.submit([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "sleep_for(100 ms)" << std::endl;
        });
}