#include "Concurrency05.h" 
#include <thread>
#include <atomic>
#include <iostream>
namespace {
    // 多线程的松散操作
    std::atomic<int> x(0), y(0), z(0); // ①
    std::atomic<bool> go(false);       // ②
    unsigned const loop_count = 10;
    struct read_values
    {
        int x, y, z;
    };
    read_values values1[loop_count];
    read_values values2[loop_count];
    read_values values3[loop_count];
    read_values values4[loop_count];
    read_values values5[loop_count];
    void increment(std::atomic<int>* var_to_inc, read_values* values)
    {
        while (!go) //  ③旋转，等待信号
            std::this_thread::yield();
        for (unsigned i = 0; i < loop_count; ++i)
        {
            values[i].x = x.load(std::memory_order_relaxed);
            values[i].y = y.load(std::memory_order_relaxed);
            values[i].z = z.load(std::memory_order_relaxed);
            var_to_inc->store(i + 1, std::memory_order_relaxed); // ④
            std::this_thread::yield();
        }
    }
    void read_vals(read_values* values)
    {
        while (!go) // ⑤旋转，等待信号
            std::this_thread::yield();
        for (unsigned i = 0; i < loop_count; ++i)
        {
            values[i].x = x.load(std::memory_order_relaxed);
            values[i].y = y.load(std::memory_order_relaxed);
            values[i].z = z.load(std::memory_order_relaxed);
            std::this_thread::yield();
        }
    }
    void print(read_values* v)
    {
        for (unsigned i = 0; i < loop_count; ++i)
        {
            if (i)
                std::cout << ",";
            std::cout << "(" << v[i].x << "," << v[i].y << "," << v[i].z << ")";
        }
        std::cout << std::endl;
    }
}
void Concurrency05_06() {
    std::thread t1(increment, &x, values1);
    std::thread t2(increment, &y, values2);
    std::thread t3(increment, &z, values3);
    std::thread t4(read_vals, values4);
    std::thread t5(read_vals, values5);
    go = true; // ⑥开始执行主循环的信号
    t5.join();
    t4.join();
    t3.join();
    t2.join();
    t1.join();
    print(values1); // ⑦打印最终的值
    print(values2);
    print(values3);
    print(values4);
    print(values5);
}
//   本质上这是一个非常简单的程序。你有三个共享的全局原子变量①和五个线程，
// 每个线程选好10次，用memory_order_relaxed读取三个原子变量的值，并将其存
// 储在数组中。这三个线程中的每个线程每次通过循环④更新其中一个原子变量，
// 而其它两个线程只是读取。一旦所有的线程都被链接，你就打印由每个线程存储在
// 数组中的值⑦。
//   原子变量go②用来确保所有的线程尽可能靠近相同的时间开始循环。启动一个线
// 程是一个昂贵的操作，若没有明确的延迟，第一个线程会在最后一个线程开始前就
// 结束了。每个线程在进入主循环之前等待go变成true③、⑤，仅当所有的线程都已
// 经开始后⑥，go才被设置成true。
// 4 理解松散顺序
// 强烈建议避免松散的原子操作(memory_order_relaxed),除非绝对必要；
// 即便绝对必要，也应该及其谨慎地使用。
