#include "Concurrency06.h" 
#include <exception>
#include <stack>
#include <mutex>
#include <memory>
// 6.��ƻ������Ĳ������ݽṹ
// 6.1 Ϊ������Ƶĺ���
// ���ݽṹ���̰߳�ȫ�����ᶪʧ���ƻ����ݣ�ά�����в�����������û�в�ȷ���ľ�������
// ����Ԫ(mutex)ʵ�������л�(serialization)
// ����������ݽṹ��׼�򣺱�֤��ȡ��ȫ�����������Ĳ�����ȡ
// ���ݴ�ȡ��ȫ����:
// A.��֤�����ݽṹ�����Ա�����߳��ƻ�ʱ��״̬�����κ������߳̿�����
// B.ע��������ݽṹ�ӿ������еľ�������ͨ��Ϊ���������ṩ�������������ṩ�������衣
// C.ע�⵱��������ʱ�����ݽṹ����������֤�����Բ����ƻ��ġ�
// D.��ʹ�����ݽṹʱ��ͨ���������ķ�Χ�ͱ���ʹ��Ƕ�����������Ͳ��������Ļ��ᡣ
// Ҫ�ر�ע�⹹�캯��������������ȷ���������ǰ��������ʼ��Ķ�ռ�ԣ����캯������������Ӧ���Ƕ�ռ�ġ�
// ���������������棺
// ���ķ�Χ�ܷ����ƣ�ʹ��һ��������һ���ֿ��������ⱻִ�У�
// ���ݽṹ�Ĳ�ͬ����ʱ�ֱ���ͬ�Ļ���Ԫ������
// �Ƿ����в�����Ҫͬ������ı�����
// ���ݽṹ��һ��С�ı��ܷ��ڲ�Ӱ���������������ͦ�߲����ԵĻ��᣿
// =======================================================================
// ����ܹ���С����Ȼ���������л��������ܹ�����޶ȵ�ʵ�ֲ����ԣ�
// =======================================================================
// C++17�ṩ�˹�������(std::shared_mutex),д��ռ����������boost::shared_mutex��ͬ��
namespace {
    // �̰߳�ȫջ���ඨ��
    struct empty_stack : std::exception
    {
        const char* what() const throw()
        {
            return "empty stack";
        }
    };

    template<typename T>
    class threadsafe_stack
    {
    private:
        std::stack<T> data;
        mutable std::mutex m;
    public:
        threadsafe_stack() {}
        threadsafe_stack(const threadsafe_stack& other)
        {
            std::lock_guard<std::mutex> lock(other.m);
            data = other.data;
        }
        threadsafe_stack& operator=(const threadsafe_stack&) = delete;

        void push(T new_value)
        {
            std::lock_guard<std::mutex> lock(m);
            data.push(std::move(new_value)); // �� �����׳��쳣
        }
        std::shared_ptr<T> pop()
        {
            std::lock_guard<std::mutex> lock(m);
            if (data.empty()) throw empty_stack(); // �� �׳��쳣ʱ����Ϊ��û���޸ģ����̰߳�ȫ��
            std::shared_ptr<T> const res(
                std::make_shared<T>(std::move(data.top()))); // �� �����׳��쳣�����̰߳�ȫ
            data.pop(); // �� �������쳣
            return res;
        }
        void pop(T& value)
        {
            std::lock_guard<std::mutex> lock(m);
            if (data.empty()) throw empty_stack();
            value = std::move(data.top()); // ��
            data.pop(); // ��
        }
        bool empty() const
        {
            std::lock_guard<std::mutex> lock(m);
            return data.empty();
        }
        size_t size() const {
            std::lock_guard<std::mutex> lock(m);
            return data.size();
        }
        // ֻ�й��캯�����������������̰߳�ȫ��
    };
}

#include <atomic>
#include <chrono>
#include <thread>
#include <iostream>
void Concurrency06_01() {
    std::cout << "06.01 �̰߳�ȫջ���ඨ��" << std::endl;
    threadsafe_stack<int> ts;
    std::atomic_bool stop = false;
    std::thread t1([&]() {
        for (int i = 0; i < 100000; i++) {
            if (!stop) {
                ts.push(i);
            }
        }
        });
    std::thread t2([&]() {
        for (int i = 0; i < 100000; i++) {
            if (!stop) {
                if (ts.empty()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(20));
                }
                else {
                    ts.pop();
                }
            }
        }
        });
    std::thread t3([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        stop.store(true);
        });
    t1.join();
    t2.join();
    t3.join();
    std::cout << "ts.size() = " << ts.size() << std::endl;
}