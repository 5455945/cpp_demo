#include "Concurrency09.h" 
#include <memory>
#include <queue>
#include <deque>
#include <mutex>
// 9.1.5 工作窃取
namespace {
    // 允许任务窃取的基于锁的队列
    class work_stealing_queue
    {
    private:
        typedef function_wrapper data_type;
        std::deque<data_type> the_queue;
        mutable std::mutex the_mutex;

    public:
        work_stealing_queue()
        {}

        work_stealing_queue(const work_stealing_queue& other) = delete;
        work_stealing_queue& operator=(
            const work_stealing_queue& other) = delete;

        void push(data_type data)
        {
            std::lock_guard<std::mutex> lock(the_mutex);
            the_queue.push_front(std::move(data));
        }

        bool empty() const
        {
            std::lock_guard<std::mutex> lock(the_mutex);
            return the_queue.empty();
        }

        bool try_pop(data_type& res)
        {
            std::lock_guard<std::mutex> lock(the_mutex);
            if (the_queue.empty())
            {
                return false;
            }

            res = std::move(the_queue.front());
            the_queue.pop_front();
            return true;
        }

        bool try_steal(data_type& res)
        {
            std::lock_guard<std::mutex> lock(the_mutex);
            if (the_queue.empty())
            {
                return false;
            }

            res = std::move(the_queue.back());
            the_queue.pop_back();
            return true;
        }
    };
}
#include <iostream>
void Concurrency09_07() {
    std::cout << __FUNCTION__ << std::endl;
    work_stealing_queue wsq;
    for (int i = 0; i < 10; i++) {
        wsq.push([]() { std::cout << __FUNCTION__ << std::endl; });
    }
    while(!wsq.empty()) {
        function_wrapper fw;
        wsq.try_pop(fw);
        std::cout << typeid(fw).name() << std::endl;
    }
}