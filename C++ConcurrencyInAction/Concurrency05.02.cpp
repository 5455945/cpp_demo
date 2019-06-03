#include "Concurrency05.h" 
#include <vector>
#include <atomic>
#include <iostream>
#include <chrono>
#include <thread>
// 5.2.3 基于std::atomic<bool>的操作
// 5.2.4 std::atomic<T*>上的操作:指针算法运算
// 5.2.5 标准原子整型的操作
// 5.2.6 std::atomic<>初级类模板
// 5.2.7 原子操作的自由函数
// 5.3 同步操作和强制顺序
namespace {
    // 从不同的线程中读取和写入变量
    std::vector<int> data;
    std::atomic_bool data_ready(false);
    void reader_thread()
    {
        while (!data_ready.load()) // ①
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        std::cout << "The answer=" << data[0] << "\n"; // ②
    }
    void writer_thread()
    {
        data.push_back(42); // ③
        data_ready = true;  // ④
    }
}
void Concurrency05_02() {
}