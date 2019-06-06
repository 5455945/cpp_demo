#include "Concurrency06.h" 
#include <memory>
// 1.通过分离数据允许并发
namespace {
    // 使用傀儡节点的简单队列
    template<typename T>
    class queue
    {
    private:
        struct node
        {
            std::shared_ptr<T> data;  // ①
            std::unique_ptr<node> next;
        };

        std::unique_ptr<node> head;
        node* tail;

    public:
        queue() :
            head(new node), tail(head.get()) // ②
        {}

        queue(const queue& other) = delete;
        queue& operator=(const queue& other) = delete;

        std::shared_ptr<T> try_pop()
        {
            if (head.get() == tail) // ③
            {
                return std::shared_ptr<T>();
            }
            std::shared_ptr<T> const res(head->data); // ④
            std::unique_ptr<node> const old_head = std::move(head); // ⑤
            head = std::move(old_head->next);
            return res; // ⑥
        }

        void push(T new_value)
        {
            std::shared_ptr<T> new_data(
                std::make_shared<T>(std::move(new_value))); // ⑦
            std::unique_ptr<node> p(new node); // ⑧
            tail->data = new_data; // ⑨
            node* const new_tail = p.get();
            tail->next = std::move(p);
            tail = new_tail;
        }
    };
}
#include <iostream>
void Concurrency06_05() {
    queue<int> tq;
    std::cout << "06.05 使用傀儡节点的简单队列" << std::endl;
    for (int i = 0; i < 1000; i++) {
        tq.push(i);
    }
    for (int i = 0; i < 1000; i++) {
        tq.try_pop();
    }
}