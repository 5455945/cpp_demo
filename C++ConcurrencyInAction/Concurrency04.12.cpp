#include "Concurrency04.h"
#include <algorithm>
#include <list>
// 4.3.4 接受超时的函数
// 4.4 使用操作同步来简化代码
// 4.4.1 带有future的函数式编程
// 1 FP风格的快速排序
namespace {
    // 快速排序的顺序实现
    template<typename T>
    std::list<T> sequential_quick_sort(std::list<T> input)
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
        auto new_lower(
            sequential_quick_sort(std::move(lower_part)));
        auto new_higher(
            sequential_quick_sort(std::move(input)));
        result.splice(result.end(), new_higher);
        // using synchronization of operations to simplify code
        result.splice(result.begin(), new_lower);
        return result;
    }
}
#include <iostream>
void Concurrency04_12() {
    std::cout << __FUNCTION__ << std::endl;
    std::list<int> input = { 2, 3, 5, 1, 0, 4, 9, 8, 6, 7 };
    std::list<int> output = sequential_quick_sort(input);
    for (auto& it : output) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}