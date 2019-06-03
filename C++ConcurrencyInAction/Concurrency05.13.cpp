#include "Concurrency05.h" 
#include <atomic>
#include <thread>
#include <cassert>
// 5.3.6 ԭ�Ӳ��������ԭ�Ӳ���
namespace {
    // �ڷ�ԭ�Ӳ�����ǿ��˳��
    bool x = false; // x��һ����ͨ�ķ�ԭ�ӱ���
    std::atomic<bool> y;
    std::atomic<int> z;

    void write_x_then_y()
    {
        x = true; // ��������ǰ�洢x
        std::atomic_thread_fence(std::memory_order_release); 
        y.store(true, std::memory_order_relaxed); // �������Ϻ�洢y
    }

    void read_y_then_x()
    {
        while (!y.load(std::memory_order_relaxed)); // �۵ȴ����㿴������#2��д��
        std::atomic_thread_fence(std::memory_order_acquire);
        if (x) // �ܽ���ȡ#1д���ֵ
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
    assert(z.load() != 0); // �ݴ˶��Բ��ᴥ��
}
