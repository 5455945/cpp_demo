#include "Concurrency05.h" 
#include <atomic>
// 5 C++内存模型和原子类型上操作
// 5.1 内存模型基础
// 5.1.1 对象和内存模型
// 5.1.2 对象、内存位置以及并发
// 5.1.3 修改顺序
// 5.2 C++中的原子操作及类型
// 5.2.1 标准原子类型
// 5.2.2 std::atomic_flag上的操作

namespace {
    // 使用std::atomic_flag的自旋锁互斥实现
    class spinlock_mutex
    {
        std::atomic_flag flag = ATOMIC_FLAG_INIT;
    public:
        //spinlock_mutex() :
        //    flag(ATOMIC_FLAG_INIT)
        spinlock_mutex()
        {
        }
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
void Concurrency05_01() {
}