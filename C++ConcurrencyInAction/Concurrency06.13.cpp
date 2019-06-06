#include "Concurrency06.h" 
#include <memory>
#include <mutex>
namespace {
    // 支持迭代的线程安全链表
    template<typename T>
    class threadsafe_list
    {
        struct node // ①
        {
            std::mutex m;
            std::shared_ptr<T> data;
            std::unique_ptr<node> next;

            node() : // ②
                next()
            {}

            node(T const& value) : // ③
                data(std::make_shared<T>(value))
            {}
        };

        node head;

    public:
        threadsafe_list()
        {}

        ~threadsafe_list()
        {
            //remove_if([](node const&) {return true; });
        }

        threadsafe_list(threadsafe_list const& other) = delete;
        threadsafe_list& operator=(threadsafe_list const& other) = delete;

        void push_front(T const& value)
        {
            std::unique_ptr<node> new_node(new node(value)); // ④
            std::lock_guard<std::mutex> lk(head.m);
            new_node->next = std::move(head.next); // ⑤
            head.next = std::move(new_node); // ⑥
        }

        template<typename Function>
        void for_each(Function f) // ⑦
        {
            node* current = &head;
            std::unique_lock<std::mutex> lk(head.m); // ⑧
            while (node* const next = current->next.get()) // ⑨
            {
                std::unique_lock<std::mutex> next_lk(next->m); // ⑩
                lk.unlock(); // 11
                f(*next->data); // 12
                current = next;
                lk = std::move(next_lk); // 13
            }
        }

        template<typename Predicate>
        std::shared_ptr<T> find_first_if(Predicate p) // 14
        {
            node* current = &head;
            std::unique_lock<std::mutex> lk(head.m);
            while (node* const next = current->next.get())
            {
                std::unique_lock<std::mutex> next_lk(next->m);
                lk.unlock();
                if (p == Predicate(*next->data)) // 15
                {
                    return next->data; //16
                }
                current = next;
                lk = std::move(next_lk);
            }
            return std::shared_ptr<T>();
        }

        //template<typename T>
        void remove_if(T p) // 17
        {
            node* current = &head;
            std::unique_lock<std::mutex> lk(head.m);
            while (node* const next = current->next.get())
            {
                std::unique_lock<std::mutex> next_lk(next->m);
                if (p == (*next->data)) // 18
                {
                    std::unique_ptr<node> old_next = std::move(current->next);
                    current->next = std::move(next->next);
                    next_lk.unlock(); // 19
                } // 20
                else
                {
                    lk.unlock(); // 21
                    current = next;
                    lk = std::move(next_lk);
                }
            }
        }
    };
}
#include <iostream>
void Concurrency06_13() {
    std::cout << "06.13 支持迭代的线程安全链表" << std::endl;
    threadsafe_list<int> tl;
    for (int i = 0; i < 100; i++) {
        tl.push_front(i);
    }
    std::shared_ptr<int> a = tl.find_first_if<int>(5);
    if (a) {
        std::cout << *a << std::endl;
    }
    std::cout << "===========================" << std::endl;
    //auto f = [](auto& x) { std::cout << x << " "; };
    tl.for_each([](auto& x) { std::cout << " " << x << " "; });
    std::cout << "===========================" << std::endl;
    std::thread t1([&]() {
        std::cout << std::endl;
        tl.for_each([&](auto& x) { std::cout << " " << x << " "; });
        std::cout << std::endl;
        });
    std::thread t2([&]() {
        std::cout << std::endl;
        tl.for_each([&](auto& x) { x *= 2; std::cout << " " << x << " "; });
        std::cout << std::endl;
        });
    std::thread t3([&]() {
        for (int i = 30; i < 60; i++) {
            tl.remove_if(i);
        }
        });
    t1.join();
    t2.join();
    t3.join();
    std::cout << "===========================" << std::endl;
}