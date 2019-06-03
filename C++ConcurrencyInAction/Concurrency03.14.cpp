#include "Concurrency03.h"
#include <iostream>
#include <mutex>  // ���� std::unique_lock
#include <shared_mutex>
#include <thread>
namespace {
    class ThreadSafeCounter {
    public:
        ThreadSafeCounter() = default;

        // ����߳�/������ͬʱ����������ֵ��
        unsigned int get() const {
            std::shared_lock<std::shared_mutex> lock(mutex_);
            return value_;
        }

        // ֻ��һ���߳�/д��������/д�̵߳�ֵ��
        void increment() {
            std::unique_lock<std::shared_mutex> lock(mutex_);
            value_++;
        }

        // ֻ��һ���߳�/д��������/д�̵߳�ֵ��
        void reset() {
            std::unique_lock<std::shared_mutex> lock(mutex_);
            value_ = 0;
        }

    private:
        mutable std::shared_mutex mutex_;
        unsigned int value_ = 0;
    };
}
void Concurrency03_14() {
    ThreadSafeCounter counter;

    auto increment_and_print = [&counter]() {
        for (int i = 0; i < 3; i++) {
            counter.increment();
            std::cout << std::this_thread::get_id() << ' ' << counter.get() << '\n';
            // ע�⣺д�� std::cout ʵ����ҲҪ����һ����ͬ����ʡ�����Ա���ʾ����ࡣ
        }
    };
    std::thread thread1(increment_and_print);
    std::thread thread2(increment_and_print);
    thread1.join();
    thread2.join();
}
// ���ͣ���������ڵ��˻��������ɡ� thread1 ��ʼʱ�����״ν���ѭ�������� increment() ��
// ������ get() ��Ȼ���������ܴ�ӡ����ֵ�� std::cout ǰ���������� thread1 ��������
// ������ thread2 ������Ȼ���㹻ʱ��һ������ȫ������ѭ���������ٻص� thread1 ���������׸�
// ѭ�������У������մ�ӡ��ֲ��ļ�����������ֵ���� 1 �� std::cout ��������ʣ�¶���ѭ����
// ��˻����ϣ�û���̱߳��������ߣ������������Ϊ����˳��