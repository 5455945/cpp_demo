#include "Concurrency07.h" 
#include <atomic>
// 7.2 无锁数据结构的例子
// ==============================================================================================
// 使用原子操作的无锁数据结构以及与之相关联的内存顺序保证是为了确保数据以正确的顺序对其它线程可见。
// ==============================================================================================
// 除了std::atomic_flag之外，C++标准并不保证其它原子操作的实现是无锁的；要看具体实现。
// 7.2.1 编写不用锁的线程安全栈
namespace {
    // 实现不适用锁的线程安全push
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
