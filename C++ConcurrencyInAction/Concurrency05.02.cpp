#include "Concurrency05.h" 
#include <vector>
#include <atomic>
#include <iostream>
#include <chrono>
#include <thread>
// 5.3 同步操作和强制顺序
// happens-before(发生于之前)
// synchronizes-with(与之同步)
namespace {
    // 从不同的线程中读取和写入变量
    std::vector<int> data;              // 数据
    std::atomic_bool data_ready(false); // 标志
    void reader_thread()
    {
        while (!data_ready.load()) // ① 标志读取发生在数据读取之前
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        std::cout << "The answer=" << data[0] << "\n"; // ②数据读取
    }
    void writer_thread()
    {
        data.push_back(42); // ③ 数据写入发生在标志写入之前
        data_ready = true;  // ④ 标志写入
    }
}
void Concurrency05_02() {
    std::thread t1(reader_thread);
    std::thread t2(writer_thread);
    t1.join();
    t2.join();
}