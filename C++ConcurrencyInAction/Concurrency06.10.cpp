#include "Concurrency06.h" 
#include <memory>
#include <mutex>
namespace {
    // 使用锁和等待的线程安全队列:try_pop()和empty()
    // 完整的代码(06.07-06.10)
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
        std::condition_variable data_cond;

        node* get_tail()
        {
            std::lock_guard<std::mutex> tail_lock(tail_mutex);
            return tail;
        }

        std::unique_ptr<node> pop_head()
        {
            std::unique_ptr<node> old_head = std::move(head);
            head = std::move(old_head->next);
            return old_head;
        }

        std::unique_lock<std::mutex> wait_for_data()
        {
            std::unique_lock<std::mutex> head_lock(head_mutex);
            data_cond.wait(head_lock, [&] {return head != get_tail(); });
            return std::move(head_lock);
        }

        std::unique_ptr<node> wait_pop_head()
        {
            std::unique_lock<std::mutex> head_lock(wait_for_data());
            return pop_head();
        }

        std::unique_ptr<node> wait_pop_head(T& value)
        {
            std::unique_lock<std::mutex> head_lock(wait_for_data());
            value = std::move(*head->data);
            return pop_head();
        }

        std::unique_ptr<node> try_pop_head()
        {
            std::lock_guard<std::mutex> head_lock(head_mutex);
            if (head.get() == get_tail())
            {
                return std::unique_ptr<node>();
            }
            return pop_head();
        }

        std::unique_ptr<node> try_pop_head(T& value)
        {
            std::lock_guard<std::mutex> head_lock(head_mutex);
            if (head.get() == get_tail())
            {
                return std::unique_ptr<node>();
            }
            value = std::move(*head->data);
            return pop_head();
        }

    public:
        threadsafe_queue() :
            head(new node), tail(head.get())
        {}
        threadsafe_queue(const threadsafe_queue& other) = delete;
        threadsafe_queue& operator=(const threadsafe_queue& other) = delete;

        std::shared_ptr<T> wait_and_pop()
        {
            std::unique_ptr<node> const old_head = wait_pop_head();
            return old_head->data;
        }

        void wait_and_pop(T& value)
        {
            std::unique_ptr<node> const old_head = wait_pop_head(value);
        }
        
        void push(T new_value)
        {
            std::shared_ptr<T> new_data(
                std::make_shared<T>(std::move(new_value)));
            std::unique_ptr<node> p(new node);
            {
                std::lock_guard<std::mutex> tail_lock(tail_mutex);
                tail->data = new_data;
                node* const new_tail = p.get();
                tail->next = std::move(p);
                tail = new_tail;
            }
            data_cond.notify_one();
        }

        std::shared_ptr<T> try_pop()
        {
            std::unique_ptr<node> const old_head = try_pop_head();
            return old_head ? old_head->data : std::shared_ptr<T>();
        }

        bool try_pop(T& value)
        {
            std::unique_ptr<node> const old_head = try_pop_head(value);
            return old_head != nullptr;
        }

        bool empty()
        {
            std::lock_guard<std::mutex> head_lock(head_mutex);
            return (head.get() == get_tail());
        }
    };
}

#include <iostream>
#include <thread>
#include <atomic>
void Concurrency06_10() {
    std::cout << "06.10 用锁和等待的线程安全队列" << std::endl;
    threadsafe_queue<int> tq;
    std::atomic_bool stop = false;
    std::thread t1([&]() {
        for (int i = 0; i < 1000; i++) {
            if (!stop) {
                tq.push(i);
            }
        }
        });
    std::thread t2([&]() {
        for (int i = 0; i < 1000; i++) {
            if (!stop) {
                if (tq.empty()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(20));
                }
                else {
                    std::shared_ptr<int> p = tq.try_pop();
                    if (p) {
                        std::cout << *p << " ";
                    }
                }
            }
        }
        std::cout << std::endl;
        });
    std::thread t3([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        stop.store(true);
        });
    t1.join();
    t2.join();
    t3.join();
}