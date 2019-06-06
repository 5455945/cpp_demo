#include "Concurrency06.h" 
#include <memory>
#include <mutex>
namespace {
    // 使用细粒度锁的线程安全队列
    template<typename T>
    class threadsafe_queue
    {
    private:
        struct node
        {
            std::shared_ptr<T> data;
            std::unique_ptr<node> next;
        };

        std::mutex head_mutex;
        std::unique_ptr<node> head;
        std::mutex tail_mutex;
        node* tail;

        node* get_tail()
        {
            std::lock_guard<std::mutex> tail_lock(tail_mutex);
            return tail;
        }

        std::unique_ptr<node> pop_head()
        {
            std::lock_guard<std::mutex> head_lock(head_mutex);
            if (head.get() == get_tail())
            {
                return nullptr;
            }
            std::unique_ptr<node> old_head = std::move(head);
            head = std::move(old_head->next);
            return old_head;
        }

    public:
        threadsafe_queue() :
            head(new node), tail(head.get())
        {}

        threadsafe_queue(const threadsafe_queue& other) = delete;
        threadsafe_queue& operator=(const threadsafe_queue& other) = delete;

        std::shared_ptr<T> try_pop()
        {
            std::unique_ptr<node> old_head = pop_head();
            return old_head ? old_head->data : std::shared_ptr<T>();
        }

        void push(T new_value)
        {
            std::shared_ptr<T> new_data(
                std::make_shared<T>(std::move(new_value)));
            std::unique_ptr<node> p(new node);
            node* const new_tail = p.get();
            std::lock_guard<std::mutex> tail_lock(tail_mutex);
            tail->data = new_data;
            tail->next = std::move(p);
            tail = new_tail;
        }
    };
}

#include <iostream>
#include <thread>
#include <atomic>
void Concurrency06_06() {
    threadsafe_queue<int> tq;
    std::cout << "06.06 使用细粒度锁的线程安全队列" << std::endl;
    std::thread t1([&]() {
        for (int i = 0; i < 100; i++) {
            tq.push(i);
        }
        });
    std::thread t2([&]() {
        for (int i = 0; i < 100; i++) {
            std::shared_ptr<int> p = tq.try_pop();
            if (p) {
                std::cout << *p << " ";
            }
            else {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                i--;
                continue;
            }
        }
        std::cout << std::endl;
        });
    t1.join();
    t2.join();
}