#include "Concurrency07.h" 
#include <atomic>
#include <memory>
namespace {
    // ȱ�ٽڵ������ջ
    template<typename T>
    class lock_free_stack
    {
    private:
        struct node
        {
            std::shared_ptr<T> data; // �� data������ָ�����
            node* next;
            node(T const& data_) :
                data(std::make_shared<T>(data_)) // �� Ϊ�·����T����std::shared_ptr
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
        std::shared_ptr<T> pop()
        {
            node* old_head = head.load();
            if (!old_head) {
                return std::shared_ptr<T>();
            }
            while (old_head && // �� �ڽ�����֮ǰ���old_head����һ����ָ��
                (!head.compare_exchange_weak(old_head, old_head->next)));
            return old_head ? old_head->data : std::shared_ptr<T>(); // �� 
        }
    };
}
#include <atomic>
#include <iostream>
#include <thread>
void Concurrency07_03() {
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
        std::shared_ptr<int> result;
        for (int i = 0; i < 1000; i++) {
            result = lfs.pop();
        }
        });
    running.store(true);
    t1.join();
    t2.join();
}
