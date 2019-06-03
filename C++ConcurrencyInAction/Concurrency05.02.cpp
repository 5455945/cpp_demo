#include "Concurrency05.h" 
#include <vector>
#include <atomic>
#include <iostream>
#include <chrono>
#include <thread>
// 5.2.3 ����std::atomic<bool>�Ĳ���
// 5.2.4 std::atomic<T*>�ϵĲ���:ָ���㷨����
// 5.2.5 ��׼ԭ�����͵Ĳ���
// 5.2.6 std::atomic<>������ģ��
// 5.2.7 ԭ�Ӳ��������ɺ���
// 5.3 ͬ��������ǿ��˳��
namespace {
    // �Ӳ�ͬ���߳��ж�ȡ��д�����
    std::vector<int> data;
    std::atomic_bool data_ready(false);
    void reader_thread()
    {
        while (!data_ready.load()) // ��
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        std::cout << "The answer=" << data[0] << "\n"; // ��
    }
    void writer_thread()
    {
        data.push_back(42); // ��
        data_ready = true;  // ��
    }
}
void Concurrency05_02() {
}