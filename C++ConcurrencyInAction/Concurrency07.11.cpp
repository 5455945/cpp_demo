#include "Concurrency07.h" 
#include <memory>
#include <thread>
#include <atomic>
namespace {
    // 使用两个引用计数从无锁栈中出栈一个结点
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
            node() : data(std::make_shared<T>()), internal_count(0) {}
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
            } while (!head.compare_exchange_strong(old_counter, new_counter));
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
            new_node.ptr->next = head.load();
            while (!head.compare_exchange_weak(new_node.ptr->next, new_node));
        }
        std::shared_ptr<T> pop()
        {
            counted_node_ptr old_head = head.load();
            for (;;)
            {
                increase_head_count(old_head);
                node* const ptr = old_head.ptr;
                if (!ptr)
                {
                    return std::shared_ptr<T>();
                }
                if (head.compare_exchange_strong(old_head, ptr->next))
                {
                    std::shared_ptr<T> res = nullptr;
                    res.swap(ptr->data);
                    int const count_increase = old_head.external_count - 2;
                    if (ptr->internal_count.fetch_add(count_increase) ==
                        -count_increase)
                    {
                        delete ptr;
                    }
                    return res;
                }
                else if (ptr->internal_count.fetch_sub(1) == 1)
                {
                    delete ptr;
                }
            }
        }
    };
}
#include <atomic>
#include <iostream>
#include <thread>
void Concurrency07_11() {
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