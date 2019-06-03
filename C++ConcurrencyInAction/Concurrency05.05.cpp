#include "Concurrency05.h" 
#include <atomic>
#include <thread>
#include <cassert>
// 2 非顺序一致的内存顺序
// 事件不再是单一的全局顺序；线程不必和事件的顺序一致；线程不必和事件的顺序一致；线程不必和事件的顺序一致。
// CPU缓存和内部缓冲区可能为相同的内存保存了不同的值。
// 即使线程正在运行相同的代码，由于其它线程中的操作没有明确的顺序约束，它们可能与事件的顺序不一致。
// 在没有其它的顺序约束时，唯一的要求是所有的线程对每个独立变量的修改顺序达成一致。

// 3 松散顺序
// 
namespace {
    // 放松操作有极少数的排序要求
    std::atomic<bool> x, y;
    std::atomic<int> z;
    void write_x_then_y()
    {
        x.store(true, std::memory_order_relaxed); // ①
        y.store(true, std::memory_order_relaxed); // ②
    }
    void read_y_then_x()
    {
        while (!y.load(std::memory_order_relaxed)); // ③
        if (x.load(std::memory_order_relaxed))      // ④
            ++z;
    }
}
void Concurrency05_05() {
    x = false;
    y = false;
    z = 0;
    std::thread a(write_x_then_y);
    std::thread b(read_y_then_x);
    a.join();
    b.join();
    assert(z.load() != 0); // ⑤
}
// assert⑤可能触发，因为x的载入④能够读到false，即便y的载入③读到了
// true并且x的存储①发生于y存储②之前。x和y是不同的变量，所以关于每
// 个操作所产生的值的可见性没有顺序保证。
