#include "Concurrency05.h" 
#include <atomic>
#include <thread>
#include <cassert>
// 5.3.6 原子操作排序非原子操作
namespace {
    // 在非原子操作上强制顺序
    bool x = false; // x是一个普通的非原子变量
    std::atomic<bool> y;
    std::atomic<int> z;

    void write_x_then_y()
    {
        x = true; // ①在屏障前存储x
        std::atomic_thread_fence(std::memory_order_release); 
        y.store(true, std::memory_order_relaxed); // ②在屏障后存储y
    }

    void read_y_then_x()
    {
        while (!y.load(std::memory_order_relaxed)); // ③等待到你看见来自#2的写入
        std::atomic_thread_fence(std::memory_order_acquire);
        if (x) // ④将读取#1写入的值
            ++z;
    }
}

void Concurrency05_13() {
    x = false;
    y = false;
    z = 0;
    std::thread a(write_x_then_y);
    std::thread b(read_y_then_x);
    a.join();
    b.join();
    assert(z.load() != 0); // ⑤此断言不会触发
}
