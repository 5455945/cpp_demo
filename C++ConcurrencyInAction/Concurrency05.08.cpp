#include "Concurrency05.h" 
#include <atomic>
#include <thread>
#include <cassert>
namespace {
    // 获取-释放操作可以在松散操作中施加顺序
    std::atomic<bool> x, y;
    std::atomic<int> z;

    void write_x_then_y()
    {
        x.store(true, std::memory_order_relaxed); // ①旋转，等待y被设为true
        y.store(true, std::memory_order_release); // ②
    }

    void read_y_then_x()
    {
        while (!y.load(std::memory_order_acquire)); // ③
        if (x.load(std::memory_order_relaxed))      // ④
            ++z;
    }
}
void Concurrency05_08() {
    for (int i = 0; i < 100; i++) {
        x = false;
        y = false;
        z = 0;
        std::thread a(write_x_then_y);
        std::thread b(read_y_then_x);
        a.join();
        b.join();
        assert(z.load() != 0); // ⑤
    }
}
// 这里对y的存储更改为使用memory_order_release,并且让对y的载入使
// 用memory_order_qcquire,实际上就相当于对x上的操作施加了一个顺序。
// 最终，对y的加载③将会看到由存储写下的true②。因为存储使用memory_
// order_release并且载入使用memory_order_acquire，存储与载入同步。对x的
// 存储①发生在对y的存储②之前，因为它们在同一个线程里。因为对y的存储与从y的
// 载入同步。对x的存储同样发生于从y的载入之前，并且推而广之发生于从x的载入④
// 之前。于是，从x的载入必然读到true，而且断言⑤不会触发。如果从y的载入不在
// while循环里，就不一定是这个情况；从y的载入可能读到false，在这种情况下，
// 对从x读取到的值就没有要求了。为了提供同步，获取和释放操作必须配对。由释放操
// 作存储的值必须被获取操作看到，以便两者中的任意一个生效。如果②处的存储或③处
// 的载入有一个松散操作，对x的访问就没有顺序，因此就不能确保④处的载入读取true，
// 且assert会被触发。
