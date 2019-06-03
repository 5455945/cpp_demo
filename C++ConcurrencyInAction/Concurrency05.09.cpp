#include "Concurrency05.h" 
#include <atomic>
#include <thread>
#include <cassert>
// 6 ��ȡ-�ͷ�˳�򴫵���ͬ��
namespace {
    // ʹ�û�ȡ���ͷ�˳��Ĵ�����ͬ��
    std::atomic<int> data[5];
    std::atomic<bool> sync1(false), sync2(false);
    void thread_1()
    {
        data[0].store(42, std::memory_order_relaxed);
        data[1].store(97, std::memory_order_relaxed);
        data[2].store(17, std::memory_order_relaxed);
        data[3].store(-141, std::memory_order_relaxed);
        data[4].store(2003, std::memory_order_relaxed);
        sync1.store(true, std::memory_order_release); // ������sync1
    }
    void thread_2()
    {
        while (!sync1.load(std::memory_order_acquire)); // ��ѭ��ֱ��sync1������
        sync2.store(true, std::memory_order_release);   // ������sync2
    }
    void thread_3()
    {
        while (!sync2.load(std::memory_order_acquire)); // ��ѭ��ֱ��sync2������
        assert(data[0].load(std::memory_order_relaxed) == 42);
        assert(data[1].load(std::memory_order_relaxed) == 97);
        assert(data[2].load(std::memory_order_relaxed) == 17);
        assert(data[3].load(std::memory_order_relaxed) == -141);
        assert(data[4].load(std::memory_order_relaxed) == 2003);
    }
}
void Concurrency05_09() {
    std::thread t1(thread_1);
    std::thread t2(thread_2);
    std::thread t3(thread_3);
    t1.join();
    t2.join();
    t3.join();
}
