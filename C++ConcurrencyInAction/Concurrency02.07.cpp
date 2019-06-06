#include "Concurrency02.h"
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
namespace {
    // 生成一批线程并等待它们完成
    void do_work(unsigned id)
    {}

    void f()
    {
        std::vector<std::thread> threads;
        for (unsigned i = 0; i < 20; ++i)
        {
            threads.push_back(std::thread(do_work, i)); // 生成线程
        }
        std::for_each(threads.begin(), threads.end(),
            std::mem_fn(&std::thread::join)); // 轮流在每个线程上调用join(),std::mem_fn和std::bind
    }
}
void Concurrency02_07() {
    f();
}