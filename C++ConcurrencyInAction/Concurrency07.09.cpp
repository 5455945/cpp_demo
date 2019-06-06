#include "Concurrency07.h" 
#include <atomic>
#include <memory>
// 7.2.4 使用引用计数检测结点
namespace {
    // 使用无锁的std::shared_ptr<>的无锁栈实现
    template<typename T>
    class lock_free_stack
    {
    private:
        struct node
        {
            std::shared_ptr<T> data;
            std::shared_ptr<node> next;
            node(T const& data_) :
                data(std::make_shared<T>(data_))
            {}
        };
        std::shared_ptr<node> head = nullptr;
    public:
        void push(T const& data)
        {
            std::shared_ptr<node> const new_node = std::make_shared<node>(data);
            new_node->next = head;
            while (!std::atomic_compare_exchange_weak(
                &head, &new_node->next, new_node));
        }
        std::shared_ptr<T> pop()
        {
            if (!head) {
                return std::make_shared<T>();
            }
            std::shared_ptr<node> old_head = std::atomic_load(&head);
            while (old_head && !std::atomic_compare_exchange_weak(
                &head, &old_head, old_head->next));
            return old_head ? old_head->data : std::shared_ptr<T>();
        }
    };
}
#include <atomic>
#include <iostream>
#include <thread>
// 不完善的
void Concurrency07_09() {
    //std::cout << __FUNCTION__ << std::endl;
    //lock_free_stack<int> lfs;
    //std::atomic_bool running = false;
    //std::thread t1([&]() {
    //    if (!running) {
    //        std::this_thread::yield();
    //    }
    //    for (int i = 0; i < 1000; i++) {
    //        lfs.push(i);
    //    }
    //    });
    //std::thread t2([&]() {
    //    if (!running) {
    //        std::this_thread::yield();
    //    }
    //    std::shared_ptr<int> result;
    //    for (int i = 0; i < 1000; i++) {
    //        result = lfs.pop();
    //    }
    //    });
    //running.store(true);
    //t1.join();
    //t2.join();
}
