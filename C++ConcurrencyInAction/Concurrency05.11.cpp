#include "Concurrency05.h" 
#include <atomic>
#include <thread>
#include <vector>
// 5.3.4 释放序列和synchronizes-with
namespace {
    // 使用原子操作从队列中读取值
    std::vector<int> queue_data;
    std::atomic<int> count;

    void populate_queue()
    {
        unsigned const number_of_items = 20;
        queue_data.clear();
        for (unsigned i = 0; i < number_of_items; ++i)
        {
            queue_data.push_back(i);
        }

        count.store(number_of_items, std::memory_order_release); // ①最初的存储
    }

    void consume_queue_items()
    {
        while (true)
        {
            int item_index;
            if ((item_index = count.fetch_sub(1, std::memory_order_acquire)) <= 0) // ②一个读-修改-写操作
            {
                //wait_for_more_items(); // ③等待更多项目
                continue;
            }
            //process(queue_data[item_index - 1]); // ④读取queue_data是安全的
        }
    }
}

void Concurrency05_11() {
    //std::thread a(populate_queue);
    //std::thread b(consume_queue_items);
    //std::thread c(consume_queue_items);
    //a.join();
    //b.join();
    //c.join();
}
