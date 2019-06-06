#include "Concurrency04.h" 
#include <mutex>
#include <condition_variable>
#include <queue>
#include <iostream>
namespace {
    // 提取push()和wait_and_pop()
    template<typename T>
    class threadsafe_queue
    {
    private:
        std::mutex mut;
        std::queue<T> data_queue;
        std::condition_variable data_cond;
    public:
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
    };


    struct data_chunk
    {};

    data_chunk prepare_data() {
        return data_chunk();
    }
    bool more_data_to_prepare() {
        return true;
    }
    void process(data_chunk& dc) {
        std::cout << __FUNCTION__ << std::endl;
    };
    bool is_last_chunk(data_chunk) {
        return true;
    }

    threadsafe_queue<data_chunk> data_queue;

    void data_preparation_thread()
    {
        static int i = 0;
        while (more_data_to_prepare() && (i++ < 10))
        {
            data_chunk const data = prepare_data();
            data_queue.push(data);
        }
    }

    void data_processing_thread()
    {
        while (true)
        {
            data_chunk data;
            data_queue.wait_and_pop(data);
            process(data);
            if (is_last_chunk(data)) // 只取一个
                break;
        }
    }
}
void Concurrency04_04() {
    std::thread t1([]() {
        data_preparation_thread();
        });
    std::thread t2([]() {
        data_processing_thread();
        });
    t1.join();
    t2.join();
}