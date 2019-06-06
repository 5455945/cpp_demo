#include "Concurrency06.h" 
#include <memory>
// 6.2.3 使用细粒度锁和条件变量的线程安全队列
namespace {
    // 一个简单的单线程队列实现 ***单线程***
    template<typename T>
    class queue
    {
    private:
        struct node
        {
            T data;
            std::unique_ptr<node> next;

            node(T data_) :
                data(std::move(data_))
            {}
        };

        std::unique_ptr<node> head;
        node* tail;

    public:
        queue() :
            tail(nullptr)
        {}

        queue(const queue& other) = delete;
        queue& operator=(const queue& other) = delete;

        std::shared_ptr<T> try_pop()
        {
            if (!head)
            {
                return std::shared_ptr<T>();
            }
            std::shared_ptr<T> const res(
                std::make_shared<T>(std::move(head->data)));
            std::unique_ptr<node> const old_head = std::move(head);
            head = std::move(old_head->next);
            return res;
        }

        void push(T new_value)
        {
            std::unique_ptr<node> p(new node(std::move(new_value)));
            node* const new_tail = p.get();
            if (tail)
            {
                tail->next = std::move(p);
            }
            else
            {
                head = std::move(p);
            }
            tail = new_tail;
        }

        size_t size() const {
            size_t size = 0;
            node* p = head.get();
            while (p) {
                size++;
                p = p->next.get();
            }
            return size;
        }
    };
}
#include <iostream>
void Concurrency06_04() {
    queue<int> q1;
    std::cout << "06.04 一个简单的单线程队列实现" << std::endl;
    for (int i = 0; i < 100; i++) {
        q1.push(i);
    }
    size_t size = q1.size();
    std::cout << size << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << *q1.try_pop() << " ";
    }
    std::cout << std::endl;
}