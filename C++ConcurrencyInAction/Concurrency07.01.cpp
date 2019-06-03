#include "Concurrency07.h" 
#include <atomic>
namespace {
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

void Concurrency07_01() {

}