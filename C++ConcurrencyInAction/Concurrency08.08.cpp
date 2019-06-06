#include "Concurrency08.h" 
#include <future>
namespace {
    // 使用std::async的std::for_each的并行版本
    template<typename Iterator, typename Func>
    void parallel_for_each(Iterator first, Iterator last, Func f)
    {
        unsigned long const length = std::distance(first, last);

        if (!length)
            return;

        unsigned long const min_per_thread = 25;

        if (length < (2 * min_per_thread))
        {
            std::for_each(first, last, f);
        }
        else
        {
            Iterator const mid_point = first + length / 2;
            std::future<void> first_half =
                std::async(&parallel_for_each<Iterator, Func>,
                    first, mid_point, f);
            parallel_for_each(mid_point, last, f);
            first_half.get();
        }
    }
}
#include <array>
#include <numeric>
#include <iostream>
void Concurrency08_08() {
    std::cout << __FUNCTION__ << std::endl;
    std::array<int, 100> a;
    std::iota(a.begin(), a.end(), 2);
    parallel_for_each(a.begin(), a.end(), [](int& a) { a += 1; });
    for (auto& it : a) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}