#include "Concurrency09.h" 
#include <deque>
#include <future>
#include <memory>
#include <functional>
#include <iostream>
#include <iostream>
namespace {
    // 使用可等待任务线程池的parallel_accumulate
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
        // rest as before
    };

    template<typename Iterator, typename T>
    T parallel_accumulate(Iterator first, Iterator last, T init)
    {
        unsigned long const length = (unsigned long)std::distance(first, last);

        if (!length)
            return init;

        unsigned long const block_size = 25;
        unsigned long const num_blocks = (length + block_size - 1) / block_size;

        std::vector<std::future<T> > futures(num_blocks - 1);
        thread_pool pool;

        Iterator block_start = first;
        for (unsigned long i = 0; i < (num_blocks - 1); ++i)
        {
            Iterator block_end = block_start;
            std::advance(block_end, block_size);
            //futures[i] = pool.submit(accumulate_block<Iterator, T>());
            futures[i] = pool.submit([block_start, block_end]()
                {
                    accumulate_block<Iterator, T> a;
                    return a(block_start, block_end);
                });
            block_start = block_end;
        }
        T last_result = accumulate_block<Iterator, T>()(block_start, last);
        T result = init;
        for (unsigned long i = 0; i < (num_blocks - 1); ++i)
        {
            result += futures[i].get();
        }
        result += last_result;
        return result;
    }
}
#include <vector>
#include <iostream>
#include <numeric>
void Concurrency09_03() {
    std::cout << __FUNCTION__ << std::endl;
    std::vector<int> v(1000);
    std::iota(v.begin(), v.end(), 1);
    int sum = parallel_accumulate<std::vector<int>::iterator, int>(v.begin(), v.end(), 0);
    std::cout << "sum = " << sum << std::endl;
}