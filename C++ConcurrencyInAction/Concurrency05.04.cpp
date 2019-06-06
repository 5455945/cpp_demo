#include "Concurrency05.h" 
#include <atomic>
#include <thread>
#include <cassert>
// 并发是和cpu相关的，而数据是在内存中的；cpu和内存之间还有cpu的缓存(一级缓存/二级缓存等)
// ==================================================================================================
// 下面这个类比不一定恰当：
// 如果是单核心的模拟并发，内存顺序应该就是顺序的；所以应该考虑的是多核和多cpu的情形。
// 对于内存数据data0，
// cpu的核c1获得data0到缓存m1;
// cpu的核c2获取data0到缓存m2;
// c1修改了m1的值，未写回内存data0,
// c2需改了m2的值，写回内存data0，这是m2与data0一致，与m1不同
// cpu的核c3获取data0到缓存m3;与m2一致，与m1不同。
// ==================================================================================================
// 不同cpu获得同一内存的数据时机可能不同，导致修改的时候是否确认不同缓存和内存的同一数据是否一致。
// 5.3.3 原子操作的内存顺序
// 有六种内存顺序选项可以应用于原子类型上的操作:
// memory_order_relaxed
// memory_order_consume
// memory_order_acquire
// memory_order_release
// memory_order_acq_rel
// memory_order_seq_cst
// 除非你为某个特定的操作作出指定，原子类型上的所有操作的内存顺序预选项都是:memory_order_seq_cst,这是最严格的选项。
// 内存顺序分为三类:
// 顺序一致(sequentially consistent)顺序:memory_order_seq_cst
// 获得-释放(acquire-release)顺序:memory_order_consume、memory_order_acquire、memory_order_release、memory_order_acq_rel
// 松散(relaxed)顺序:memory_order_relaxed

// 1 顺序一致顺序
namespace {
    // 顺序一致隐含着总体顺序
    // 这里x的读和写顺序一致；y的读和写也顺序一致。
    // 也就说不同线程一定是看到相同的值；
    // 当A线程修改了x之后(内存里的x值)，B线程读取x时，一定时修改之后的值。不可能使用缓存中之前的x的值。
    // 这个机制时通过std::memory_order_seq_cst控制，这将导致线程之间(cpu不同核之间)频繁的和内存同步，
    // 一旦有修改，其它线程必须从内存中获取新值。
    // 这里需要考虑cpu核心的寄存器，cpu的缓存，和内存。
    std::atomic<bool> x, y;
    std::atomic<int> z;
    void write_x()
    {
        x.store(true, std::memory_order_seq_cst); // ①
    }
    void write_y()
    {
        y.store(true, std::memory_order_seq_cst); // ②
    }
    void read_x_then_y()
    {
        while (!x.load(std::memory_order_seq_cst));
        if (y.load(std::memory_order_seq_cst)) // ③
            ++z;
    }
    void read_y_then_x()
    {
        while (!y.load(std::memory_order_seq_cst));
        if (x.load(std::memory_order_seq_cst)) // ④
            ++z;
    }
}
void Concurrency05_04() {
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
        assert(z.load() != 0); // ⑤ 这个断言不会被触发，z!=0
    }
}