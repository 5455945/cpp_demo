#include "Concurrency03.h"
#include <iostream>
#include <mutex>  // 对于 std::unique_lock
#include <shared_mutex>
#include <thread>
namespace {
    class ThreadSafeCounter {
    public:
        ThreadSafeCounter() = default;

        // 多个线程/读者能同时读计数器的值。
        unsigned int get() const {
            std::shared_lock<std::shared_mutex> lock(mutex_);
            return value_;
        }

        // 只有一个线程/写者能增加/写线程的值。
        void increment() {
            std::unique_lock<std::shared_mutex> lock(mutex_);
            value_++;
        }

        // 只有一个线程/写者能重置/写线程的值。
        void reset() {
            std::unique_lock<std::shared_mutex> lock(mutex_);
            value_ = 0;
        }

    private:
        mutable std::shared_mutex mutex_;
        unsigned int value_ = 0;
    };
}
void Concurrency03_14() {
    ThreadSafeCounter counter;

    auto increment_and_print = [&counter]() {
        for (int i = 0; i < 3; i++) {
            counter.increment();
            std::cout << std::this_thread::get_id() << ' ' << counter.get() << '\n';
            // 注意：写入 std::cout 实际上也要由另一互斥同步。省略它以保持示例简洁。
        }
    };
    std::thread thread1(increment_and_print);
    std::thread thread2(increment_and_print);
    thread1.join();
    thread2.join();
}
// 解释：下列输出在单核机器上生成。 thread1 开始时，它首次进入循环并调用 increment() ，
// 随后调用 get() 。然而，在它能打印返回值到 std::cout 前，调度器将 thread1 置于休眠
// 并唤醒 thread2 ，它显然有足够时间一次运行全部三个循环迭代。再回到 thread1 ，它仍在首个
// 循环迭代中，它最终打印其局部的计数器副本的值，即 1 到 std::cout ，再运行剩下二个循环。
// 多核机器上，没有线程被置于休眠，且输出更可能为递增顺序。