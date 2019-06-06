#include "Concurrency10.h" 
#include <cassert>
#include <atomic>
#include <thread>
#include <future>
#include <memory>
namespace {
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
    void test_concurrent_push_and_pop_on_empty_queue()
    {
        threadsafe_queue<int> q;

        std::promise<void> go, push_ready, pop_ready;
        std::shared_future<void> ready(go.get_future());

        std::future<void> push_done;
        std::future<std::shared_ptr<int>> pop_done;

        try
        {
            push_done = std::async(std::launch::async,
                [&q, ready, &push_ready]()
                {
                    push_ready.set_value();
                    ready.wait();
                    q.push(42);
                }
            );
            pop_done = std::async(std::launch::async,
                [&q, ready, &pop_ready]()
                {
                    pop_ready.set_value();
                    ready.wait();
                    return q.try_pop();
                }
            );
            push_ready.get_future().wait();
            pop_ready.get_future().wait();
            go.set_value();

            push_done.get();
            std::shared_ptr<int> pop_ptr = pop_done.get();
            //assert(*pop_done.get() == 42);
            //assert(q.empty());
        }
        catch (...)
        {
            go.set_value();
            throw;
        }
    }
}

void Concurrency10_01() {
    test_concurrent_push_and_pop_on_empty_queue();
}