#include "Concurrency05.h" 
#include <atomic>
#include <thread>
#include <vector>
// 5.3.4 �ͷ����к�synchronizes-with
namespace {
    // ʹ��ԭ�Ӳ����Ӷ����ж�ȡֵ
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

        count.store(number_of_items, std::memory_order_release); // ������Ĵ洢
    }

    void consume_queue_items()
    {
        while (true)
        {
            int item_index;
            if ((item_index = count.fetch_sub(1, std::memory_order_acquire)) <= 0) // ��һ����-�޸�-д����
            {
                //wait_for_more_items(); // �۵ȴ�������Ŀ
                continue;
            }
            //process(queue_data[item_index - 1]); // �ܶ�ȡqueue_data�ǰ�ȫ��
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
