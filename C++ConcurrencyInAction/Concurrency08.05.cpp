#include "Concurrency08.h" 
#include <algorithm>
#include <future>
#include <numeric>
#include <thread>
namespace {
    // 使用std::async的std::accumulate的异常安全并行版本
    template<typename Iterator, typename T>
    T parallel_accumulate(Iterator first, Iterator last, T init)
    {
        unsigned long const length = std::distance(first, last);
        unsigned long const max_chunk_size = 25;
        if (length <= max_chunk_size)
        {
            return std::accumulate(first, last, init);
        }
        else
        {
            Iterator mid_point = first;
            std::advance(mid_point, length / 2);
            std::future<T> first_half_result =
                std::async(parallel_accumulate<Iterator, T>,
                    first, mid_point, init);
            T second_half_result = parallel_accumulate(mid_point, last, T());
            return first_half_result.get() + second_half_result;
        }
    }
}
#include <list>
#include <iostream>
#include <vector>
void Concurrency08_05() {
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
    std::cout << "sum = " << sum << std::endl;
}