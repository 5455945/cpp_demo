#include "Concurrency04.h"
#include <algorithm>
#include <future>
#include <list>
// FP风格并行快速排序
namespace {
    template<typename T>
    std::list<T> parallel_quick_sort(std::list<T> input)
    {
        if (input.empty())
        {
            return input;
        }
        std::list<T> result;
        result.splice(result.begin(), input, input.begin());
        T const& pivot = *result.begin();
        auto divide_point = std::partition(input.begin(), input.end(),
            [&](T const& t) {return t < pivot; });
        std::list<T> lower_part;
        lower_part.splice(lower_part.end(), input, input.begin(),
            divide_point);
        std::future<std::list<T> > new_lower(
            std::async(&parallel_quick_sort<T>, std::move(lower_part)));
        auto new_higher(
            parallel_quick_sort(std::move(input)));
        result.splice(result.end(), new_higher);
        result.splice(result.begin(), new_lower.get());
        return result;
    }

}
#include <iostream>
void Concurrency04_13() {
    std::cout << __FUNCTION__ << std::endl;
    std::list<int> input = { 2, 3, 5, 1, 0, 4, 9, 8, 6, 7 };
    std::list<int> output = parallel_quick_sort(input);
    for (auto& it : output) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}