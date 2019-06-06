#include "Concurrency07.h" 
#include <atomic>
// 7.2 �������ݽṹ������
// ==============================================================================================
// ʹ��ԭ�Ӳ������������ݽṹ�Լ���֮��������ڴ�˳��֤��Ϊ��ȷ����������ȷ��˳��������߳̿ɼ���
// ==============================================================================================
// ����std::atomic_flag֮�⣬C++��׼������֤����ԭ�Ӳ�����ʵ���������ģ�Ҫ������ʵ�֡�
// 7.2.1 ��д���������̰߳�ȫջ
namespace {
    // ʵ�ֲ����������̰߳�ȫpush
    template<typename T>
    class lock_free_stack
    {
    private:
        struct node
        {
            T data;
            node* next;
            node(T const& data_) :
                data(data_)
            {}
        };
        std::atomic<node*> head = nullptr;
    public:
        void push(T const& data)
        {
            node* const new_node = new node(data);
            new_node->next = head.load();
            while (!head.compare_exchange_weak(new_node->next, new_node));
        }
        void pop(T& result)
        {
            node* old_head = head.load();
            if (!old_head) {
                return;
            }
            while (!head.compare_exchange_weak(old_head, old_head->next));
            result = old_head->data;
        }
    };
}
#include <thread>
#include <atomic>
#include <iostream>
void Concurrency07_02() {
    std::cout << __FUNCTION__ << std::endl;
    lock_free_stack<int> lfs;
    std::atomic_bool running = false;
    std::thread t1([&]() {
        if (!running) {
            std::this_thread::yield();
        }
        for (int i = 0; i < 1000; i++) {
            lfs.push(i);
        }
        });
    std::thread t2([&]() {
        if (!running) {
            std::this_thread::yield();
        }
        int result = 0;
        for (int i = 0; i < 1000; i++) {
            lfs.pop(result);
        }
        });
    running.store(true);
    t1.join();
    t2.join();
}
