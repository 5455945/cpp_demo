#include "Concurrency05.h" 
#include <atomic>
#include <thread>
#include <cassert>
// 5 获取-释放顺序
// 获取释放顺序是松散顺序的进步，操作仍然没有总的顺序，但的确引入了一些同步。
// 在这种模型下，原子载入是获取(aquire)操作(memory_order_acquire)，原子存储
// 是释放(release)操作(memory_order_release)，原子的读-修改-写操作(例如：
// fetch_add()/exehange())是获取、释放或两者兼备(memory_order_qcq_rel)。
// 同步在进行释放的线程和获取的线程之间是对偶的。释放操作与读取写入值的获取操作同步。
// 这意味着不同的线程仍然可以看到不同的排序，但这些顺序是收到限制的。
namespace {
    // 获取-释放并不意味着总体排序
    std::atomic<bool> x, y;
    std::atomic<int> z;
    void write_x()
    {
        x.store(true, std::memory_order_release);
    }
    void write_y()
    {
        y.store(true, std::memory_order_release);
    }
    void read_x_then_y()
    {
        while (!x.load(std::memory_order_acquire));
        if (y.load(std::memory_order_acquire)) // ①
            ++z;
    }
    void read_y_then_x()
    {
        while (!y.load(std::memory_order_acquire));
        if (x.load(std::memory_order_acquire)) // ②
            ++z;
    }
}
void Concurrency05_07() {
    for (int i = 0; i < 100; i++) {
        x = false;
        y = false;
        z = 0;
        std::thread a(write_x);
        std::thread b(write_y);
        std::thread c(read_x_then_y);
        std::thread d(read_y_then_x);
        a.join();
        b.join();
        c.join();
        d.join();
        assert(z.load() != 0); // ③
    }
}
// 这个例子中断言③可以触发，因为对x的载入②和对y的载入①都读取false是可能的。
// x和y由不同的线程写入，所以每种情况下从释放到获取的顺序对于另外一个线程中的
// 操作是没有影响的。
// 这是因为在每个线程内部x/y并没有依赖关系(在乱序cpu指令可以重排的情况下)
