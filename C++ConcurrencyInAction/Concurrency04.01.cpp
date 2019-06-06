#include "Concurrency04.h" 
#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
// 4 同步并发操作
// 4.1 等待事件或其它条件
// 4.1.1 用条件变量等待条件
namespace {
    // 使用std::condition_variable等待数据
    struct data_chunk
    {};
    std::mutex mut;
    std::queue<data_chunk> data_queue;
    std::condition_variable data_cond;
    bool more_data_to_prepare()
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }

    data_chunk prepare_data()
    {
        return data_chunk();
    }

    void process(data_chunk&)
    {}

    bool is_last_chunk(data_chunk&)
    {
        return true;
    }

    void data_preparation_thread()
    {
        while (more_data_to_prepare())
        {
            data_chunk const data = prepare_data();
            std::lock_guard<std::mutex> lk(mut);
            data_queue.push(data);
            data_cond.notify_one();
        }
    }

    void data_processing_thread()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lk(mut);
            data_cond.wait(lk, [] {return !data_queue.empty(); });
            data_chunk data = data_queue.front();
            data_queue.pop();
            lk.unlock();
            process(data);
            if (is_last_chunk(data))
                break;
        }
    }
}
void Concurrency04_01() {
    std::thread t1(data_preparation_thread);
    std::thread t2(data_processing_thread);
    t1.join();
    t2.join();
}