#include "Concurrency08.h" 
#include <atomic>
#include <future>
#include <thread>
namespace {
    // 使用std::async实现的并行查找算法
    template<typename Iterator, typename MatchType>
    Iterator parallel_find_impl(Iterator first, Iterator last, MatchType match,
        std::atomic<bool>& done)
    {
        try
        {
            unsigned long const length = std::distance(first, last);
            unsigned long const min_per_thread = 25;
            if (length < (2 * min_per_thread))
            {
                for (; (first != last) && !done.load(); ++first)
                {
                    if (*first == match)
                    {
                        done = true;
                        return first;
                    }
                }
                return last;
            }
            else
            {
                Iterator const mid_point = first + (length / 2);
                std::future<Iterator> async_result =
                    std::async(&parallel_find_impl<Iterator, MatchType>,
                        mid_point, last, match, std::ref(done));
                Iterator const direct_result =
                    parallel_find_impl(first, mid_point, match, done);
                return (direct_result == mid_point) ?
                    async_result.get() : direct_result;
            }
        }
        catch (...)
        {
            done = true;
            throw;
        }
    }

    template<typename Iterator, typename MatchType>
    Iterator parallel_find(Iterator first, Iterator last, MatchType match)
    {
        std::atomic<bool> done(false);
        return parallel_find_impl(first, last, match, done);
    }
}
#include <atomic>
#include <array>
#include <numeric>
#include <iostream>
void Concurrency08_10() {
    std::cout << __FUNCTION__ << std::endl;
    std::atomic<bool> done = false;
    std::array<int, 100> a;
    std::iota(a.begin(), a.end(), 2);
    int x = 98;
    auto result = parallel_find_impl(a.begin(), a.end(), x, done);
    if (result != a.end()) {
        std::cout << "parallel_find_impl 找到 " << *result << std::endl;
    }
    else {
        std::cout << "parallel_find_impl 没找到 " << x << std::endl;
    }
}