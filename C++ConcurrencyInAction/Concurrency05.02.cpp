#include "Concurrency05.h" 
#include <vector>
#include <atomic>
#include <iostream>
#include <chrono>
#include <thread>
// 5.3 ͬ��������ǿ��˳��
// happens-before(������֮ǰ)
// synchronizes-with(��֮ͬ��)
namespace {
    // �Ӳ�ͬ���߳��ж�ȡ��д�����
    std::vector<int> data;              // ����
    std::atomic_bool data_ready(false); // ��־
    void reader_thread()
    {
        while (!data_ready.load()) // �� ��־��ȡ���������ݶ�ȡ֮ǰ
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        std::cout << "The answer=" << data[0] << "\n"; // �����ݶ�ȡ
    }
    void writer_thread()
    {
        data.push_back(42); // �� ����д�뷢���ڱ�־д��֮ǰ
        data_ready = true;  // �� ��־д��
    }
}
void Concurrency05_02() {
    std::thread t1(reader_thread);
    std::thread t2(writer_thread);
    t1.join();
    t2.join();
}