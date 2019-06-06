#include "Concurrency07.h" 
#include <atomic>
#include <memory>
// 7.2.5 将内存模型应用至无锁栈
namespace {
    // 使用引用计数和放松原子操作的无锁栈
    template<typename T>
    class lock_free_stack
    {
    private:
        struct node;
        struct counted_node_ptr
        {
            int external_count = 0;
            node* ptr = nullptr;
        };
        struct node
        {
            std::shared_ptr<T> data;
            std::atomic<int> internal_count;
            counted_node_ptr next;
            node(T const& data_) :
                data(std::make_shared<T>(data_)),
                internal_count(0)
            {}
        };
        std::atomic<counted_node_ptr> head;
        void increase_head_count(counted_node_ptr& old_counter)
        {
            counted_node_ptr new_counter;
            do
            {
                new_counter = old_counter;
                ++new_counter.external_count;
            } while (!head.compare_exchange_strong( // 这里使用strong
                old_counter, new_counter,
                std::memory_order_acquire,
                std::memory_order_relaxed));
            old_counter.external_count = new_counter.external_count;
        }
    public:
        ~lock_free_stack()
        {
            while (pop());
        }
        void push(T const& data)
        {
            counted_node_ptr new_node;
            new_node.ptr = new node(data);
            new_node.external_count = 1;
            new_node.ptr->next = head.load(std::memory_order_relaxed);
            while (!head.compare_exchange_weak(
                new_node.ptr->next, new_node,
                std::memory_order_release,
                std::memory_order_relaxed));
        }
        std::shared_ptr<T> pop()
        {
            counted_node_ptr old_head =
                head.load(std::memory_order_relaxed);
            for (;;)
            {
                increase_head_count(old_head);
                node* const ptr = old_head.ptr;
                if (!ptr)
                {
                    return std::shared_ptr<T>();
                }
                if (head.compare_exchange_strong(
                    old_head, ptr->next, std::memory_order_relaxed))
                {
                    std::shared_ptr<T> res;
                    res.swap(ptr->data);
                    int const count_increase = old_head.external_count - 2;
                    if (ptr->internal_count.fetch_add(
                        count_increase, std::memory_order_release) == -count_increase)
                    {
                        delete ptr;
                    }
                    return res;
                }
                else if (ptr->internal_count.fetch_add(1, std::memory_order_relaxed) == 1)
                {
                    ptr->internal_count.load(std::memory_order_acquire);
                    delete ptr;
                }
            }
        }
    };
}
#include <atomic>
#include <iostream>
#include <thread>
void Concurrency07_12() {
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