#include "Concurrency05.h" 
#include <atomic>
#include <thread>
#include <cassert>
// 5.3.5 屏障
namespace {
    // 松散操作可以使用屏障来排序
    std::atomic<bool> x, y;
    std::atomic<int> z;

    void write_x_then_y()
    {
        x.store(true, std::memory_order_relaxed);            // ①
        std::atomic_thread_fence(std::memory_order_release); // ②
        y.store(true, std::memory_order_relaxed);            // ③
    }

    void read_y_then_x()
    {
        while (!y.load(std::memory_order_relaxed));          // ④
        std::atomic_thread_fence(std::memory_order_acquire); // ⑤
        if (x.load(std::memory_order_relaxed))               // ⑥
            ++z;
    }
}

void Concurrency05_12() {
    x = false;
    y = false;
    z = 0;
    std::thread a(write_x_then_y);
    std::thread b(read_y_then_x);
    a.join();
    b.join();
    assert(z.load() != 0); // ⑦
}
