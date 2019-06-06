#include "Concurrency08.h"
#include <algorithm>
#include <numeric>
// 8.2 影响并发代码性能的因素
// 8.2.1 有多少处理器
// 8.2.2 数据竞争和乒乓缓存
// 高竞争(high contention)
// 低竞争(low contention)
// 乒乓缓存(cache ping-pong)
// 8.2.3 假共享(false sharing)
// 8.2.4 数据应该多紧密
// 任务切换(task switching)
// 8.2.5 过度订阅和过多的任务切换
// 8.3 为多线程性能设计数据结构
// 8.3.1 为复杂操作划分数组元素
// 8.3.2 其它数据结构中的数据访问方式
// 8.4 为并发设计时的额外考虑
// 8.4.1 并行算法中的异常安全
// a. 增加异常安全性
// b. std::async的异常安全
// 8.4.2 可扩展性和阿姆达尔定律(Amdahl's law)
// p = \dfrac{1}{f_s + \dfrac{1-f_s}{N}}
// 8.4.3 多线程隐藏延迟
// 8.4.4 用并发提供响应性
// 8.5 在实践中设计并发代码
// 8.5.1 std::for_each的并行实现
// 8.5.2 std::find的并行实现
// 8.5.3 std::partial_sum的并行实现
// 使用屏障(barrier)
namespace {
    // std::accumulate的并行版本(来自02.08)
    template<typename Iterator, typename T>
    struct accumulate_block
    {
        void operator()(Iterator first, Iterator last, T& result)
        {
            result = std::accumulate(first, last, result);
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

        std::vector<T> results(num_threads);
        std::vector<std::thread> threads(num_threads - 1);

        Iterator block_start = first;
        for (unsigned long i = 0; i < (num_threads - 1); ++i)
        {
            Iterator block_end = block_start;
            std::advance(block_end, block_size);
            threads[i] = std::thread(
                accumulate_block<Iterator, T>(),
                block_start, block_end, std::ref(results[i]));
            block_start = block_end;
        }
        accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);

        std::for_each(threads.begin(), threads.end(),
            std::mem_fn(&std::thread::join));

        return std::accumulate(results.begin(), results.end(), init);
    }
}
#include <list>
#include <iostream>
#include <vector>
void Concurrency08_02() {
    std::cout << __FUNCTION__ << std::endl;
    std::list<int> l = { 1, 2, 5, 3, 4, 9, 6, 7, 8, 0 };
    int result = parallel_accumulate<std::list<int>::iterator, int>(l.begin(), l.end(), 0);
    std::cout << "result = " << result << std::endl;
    std::vector<int> vi;
    for (int i = 0; i < 10; ++i)
    {
        vi.push_back(i);
    }
    int sum = parallel_accumulate(vi.begin(), vi.end(), 0);
    std::cout << "sum=" << sum << std::endl;
}
