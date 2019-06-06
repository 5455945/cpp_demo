#include "Concurrency08.h" 
#include <algorithm>
#include <future>
#include <numeric>
#include <thread>
namespace {
    // std::accumulate���쳣��ȫ���а汾
    template<typename Iterator, typename T>
    struct accumulate_block
    {
        T operator()(Iterator first, Iterator last)
        {
            return std::accumulate(first, last, T());
        }
    };

    class join_threads {
    private:
        std::vector<std::thread>& threads;
    public:
        explicit join_threads(std::vector<std::thread>& threads_) :
            threads(threads_) {
        }
        ~join_threads() {
            for (unsigned long i = 0; i < threads.size(); ++i) {
                if (threads[i].joinable()) {
                    threads[i].join();
                }
            }
        }
    };
    template<typename Iterator, typename T>
    T parallel_accumulate(Iterator first, Iterator last, T init)
    {
        unsigned long const length = std::distance(first, last);

        if (!length)
            return init;

        unsigned long const min_per_thread = 25;
        unsigned long const max_threads =
            (length + min_per_thread - 1) / min_per_thread;

        unsigned long const hardware_threads =
            std::thread::hardware_concurrency();

        unsigned long const num_threads =
            std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

        unsigned long const block_size = length / num_threads;

        std::vector<std::future<T> > futures(num_threads - 1);
        std::vector<std::thread> threads(num_threads - 1);
        join_threads joiner(threads);

        Iterator block_start = first;
        for (unsigned long i = 0; i < (num_threads - 1); ++i)
        {
            Iterator block_end = block_start;
            std::advance(block_end, block_size);
            //std::packaged_task<T(Iterator, Iterator)> task(
            //    accumulate_block<Iterator, T>());
            accumulate_block<Iterator, T> task_init_obj;
            std::packaged_task<T(Iterator, Iterator)> task(task_init_obj);
            futures[i] = task.get_future();
            threads[i] = std::thread(std::move(task), block_start, block_end);
            block_start = block_end;
        }
        T last_result = accumulate_block<Iterator, T>()(block_start, last);
        T result = init;
        for (unsigned long i = 0; i < (num_threads - 1); ++i)
        {
            result += futures[i].get();
        }
        result += last_result;
        return result;
    }
}
#include <list>
#include <iostream>
#include <vector>
void Concurrency08_04() {
    std::vector<int> v;
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i);
    }
    accumulate_block<std::vector<int>::iterator, int> x;
    x(v.begin(), v.end());

    std::cout << __FUNCTION__ << std::endl;
    std::list<int> l = { 1, 2, 5, 3, 4, 9, 6, 7, 8, 0 };
    auto result = parallel_accumulate<std::list<int>::iterator, int>(l.begin(), l.end(), 0);
    std::cout << "result = " << result << std::endl;
    std::vector<unsigned long> vi;
    for (unsigned long i = 0; i < 10; ++i)
    {
        vi.push_back(i);
    }
    unsigned long sum = parallel_accumulate<std::vector<unsigned long>::iterator, unsigned long>(vi.begin(), vi.end(), 0);
    std::cout << "sum=" << sum << std::endl;
}
