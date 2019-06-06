#include "Concurrency09.h" 
#include <deque>
#include <future>
#include <memory>
#include <functional>
#include <iostream>
#include <iostream>
#include <list>
// 9.1.3 等待其它任务的任务
namespace {
    class function_wrapper
    {
        struct impl_base {
            virtual void call() = 0;
            virtual ~impl_base() {}
        };
        std::unique_ptr<impl_base> impl;
        template<typename F>
        struct impl_type : impl_base
        {
            F f;
            impl_type(F&& f_) : f(std::move(f_)) {}
            void call() { f(); }
        };
    public:
        template<typename F>
        function_wrapper(F&& f) :
            impl(new impl_type<F>(std::move(f)))
        {}

        void call() { impl->call(); }

        void operator()() {
            impl->call();
        }
        function_wrapper() = default;

        function_wrapper(function_wrapper&& other) :
            impl(std::move(other.impl))
        {}

        function_wrapper& operator=(function_wrapper&& other)
        {
            impl = std::move(other.impl);
            return *this;
        }

        //function_wrapper(const function_wrapper&) = delete;
        //function_wrapper(function_wrapper&) = delete;
        //function_wrapper& operator=(const function_wrapper&) = delete;
    };

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
    template<typename T>
    struct sorter
    {
        thread_pool pool;

        std::list<T> do_sort(std::list<T>& chunk_data)
        {
            if (chunk_data.empty())
            {
                return chunk_data;
            }

            std::list<T> result;
            result.splice(result.begin(), chunk_data, chunk_data.begin());
            T const& partition_val = *result.begin();

            typename std::list<T>::iterator divide_point =
                std::partition(
                    chunk_data.begin(), chunk_data.end(),
                    [&](T const& val) {return val < partition_val; });

            std::list<T> new_lower_chunk;
            new_lower_chunk.splice(
                new_lower_chunk.end(),
                chunk_data, chunk_data.begin(),
                divide_point);

            std::future<std::list<T>> new_lower =
                pool.submit(std::bind(&sorter::do_sort, this,
                    std::move(new_lower_chunk)));

            std::list<T> new_higher(do_sort(chunk_data));

            result.splice(result.end(), new_higher);
            while (new_lower.wait_for(std::chrono::milliseconds(1)) != 
                std::future_status::ready)
            {
                pool.run_pending_task();
            }
            result.splice(result.begin(), new_lower.get());
            return result;
        }
    };

    template<typename T>
    std::list<T> parallel_quick_sort(std::list<T> input)
    {
        if (input.empty())
        {
            return input;
        }
        sorter<T> s;
        return s.do_sort(input);
    }
}

void Concurrency09_05() {
    std::cout << __FUNCTION__ << std::endl;
    std::list<int> lSrc = {1, 9, 5, 2, 6, 3, 7,  8, 0, 5};
    std::list<int> lDst = parallel_quick_sort<int>(lSrc);
    for (auto& it : lDst) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}