#include "Concurrency07.h" 
#include <atomic>
// 7 设计无锁的并发数据结构
// 7.1 定义和结果
// 阻塞(blocking):使用互斥元，条件变量及future来同步数据的算法和数据结构被称为阻塞的算法和数据结构。
// 有些库函数的调用是阻塞的，(比如阻塞方式调用send，只有send完成才返回；如果是设置非阻塞模式，调用后即返回)
// 非阻塞(nonblocking):不适用阻塞库函数的数据结构和算法被称为非阻塞的。
// 非阻塞的数据结构不一定是无锁的(lock-free)。
// 7.1.1 非阻塞数据结构的类型
// 7.1.2 无锁数据结构
// 7.1.3 无等待数据结构(很难实现)
// 7.1.4 无锁数据结构的优点与缺点
// 使用无锁数据结构的主要原因是为了:实现最大程度的并发;第二个原因是:健壮性。
// 基于锁的容器，总是有可能一个线程必须阻塞，并在可以继续前等待另外一个线程完成。
// 互斥元锁的目的就是通过互斥元来阻止并发。
// 使用无锁数据结构时，某些线程一步步地执行操作。
// 使用无等待数据结构时，不管别的线程在做什么操作，每个线程都可以继续执行而不需要等待。(很难实现)
// 无锁数据结构不会发生死锁；但有可能存在活锁。
// 活锁：两个线程修改数据结构，每个线程的修改都会要求另一线程的操作重新执行，彼此都会一致循环和尝试。
//(除非某个线程先到达[通过协议、通过更快、或完全靠运气])
// 活锁一般是短暂的，但会降低性能
// 无锁和无等待数据结构的缺点:可能降低性能(比如乒乓缓存)，设计复杂。
namespace {
    // 使用std::atomic_flag的自旋互斥元的实现
    // 自旋锁(spin_lock);使用自旋锁来保护共享数据的代码是非阻塞的。但是并非无锁。
    class spinlock_mutex
    {
        std::atomic_flag flag = ATOMIC_FLAG_INIT;
    public:
        spinlock_mutex()/* :
            flag(ATOMIC_FLAG_INIT)*/
        {}
        void lock()
        {
            while (flag.test_and_set(std::memory_order_acquire));
        }
        void unlock()
        {
            flag.clear(std::memory_order_release);
        }
    };

}
#include <atomic>
#include <thread>
#include <iostream>
void Concurrency07_01() {
    std::cout << __FUNCTION__ << std::endl;
    spinlock_mutex sm;
    std::atomic<bool> flag = false;
    int x = 0;
    std::thread t1([&]() {
        if (!flag) {
            std::this_thread::yield();
        }
        for (int i = 0; i < 200; i++) {
            sm.lock();
            x++;
            std::cout << " *" << x << "* "; // *和=方便看输出交替
            sm.unlock();
        }
        });
    std::thread t2([&]() {
        if (!flag) {
            std::this_thread::yield();
        }
        for (int i = 1; i < 200; i++) {
            sm.lock();
            x += 2;
            std::cout << " =" << x << "= "; // *和=方便看输出交替
            sm.unlock();
        }
        });
    flag.store(true);
    t1.join();
    t2.join();
}
