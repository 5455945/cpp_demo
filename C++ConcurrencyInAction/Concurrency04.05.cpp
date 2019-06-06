#include "Concurrency04.h" 
#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>
namespace {
    // 使用条件变量的线程安全队列的完整定义
    template<typename T>
    class threadsafe_queue
    {
    private:
        mutable std::mutex mut;
        std::queue<T> data_queue;
        std::condition_variable data_cond;
    public:
        threadsafe_queue()
        {}
        threadsafe_queue(threadsafe_queue const& other)
        {
            std::lock_guard<std::mutex> lk(other.mut);
            data_queue = other.data_queue;
        }

        void push(T new_value)
        {
            std::lock_guard<std::mutex> lk(mut);
            data_queue.push(new_value);
            data_cond.notify_one();
        }

        void wait_and_pop(T& value)
        {
            std::unique_lock<std::mutex> lk(mut);
            data_cond.wait(lk, [this] {return !data_queue.empty(); });
            value = data_queue.front();
            data_queue.pop();
        }

        std::shared_ptr<T> wait_and_pop()
        {
            std::unique_lock<std::mutex> lk(mut);
            data_cond.wait(lk, [this] {return !data_queue.empty(); });
            std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
            data_queue.pop();
            return res;
        }

        bool try_pop(T& value)
        {
            std::lock_guard<std::mutex> lk(mut);
            if (data_queue.empty)
                return false;
            value = data_queue.front();
            data_queue.pop();
        }

        std::shared_ptr<T> try_pop()
        {
            std::lock_guard<std::mutex> lk(mut);
            if (data_queue.empty())
                return std::shared_ptr<T>();
            std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
            data_queue.pop();
            return res;
        }

        bool empty() const
        {
            std::lock_guard<std::mutex> lk(mut);
            return data_queue.empty();
        }

        size_t size() const
        {
            std::lock_guard<std::mutex> lk(mut);
            return data_queue.size();
        }
    };
}
void Concurrency04_05() {
    threadsafe_queue<int> qt;
    std::thread t1([&qt]() {
        for (int i = 0; i < 100; i++) {
            qt.push(i);
        }
        });
    std::thread t2([&qt]() {
        while (!qt.empty()) {
            qt.try_pop();
        }
        });
    t1.join();
    t2.join();
}