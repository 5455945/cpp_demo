#include "Concurrency03.h"
#include <mutex>
// 3.2.4 死锁:问题和解决
// 死锁(deadlock):锁定两个或更多mutex,彼此互相等待对方释放自己需要的锁
// 为了避免死锁，常见的建议是始终使用相同的顺序锁定两个互斥量;但是两个持有互斥量的对象交换时，也可能发生死锁。
// C++标准库中的std::lock可以解决同时锁定两个或多个互斥量
namespace {
    class some_big_object
    {};

    void swap(some_big_object& lhs, some_big_object& rhs)
    {}

    class X
    {
    private:
        some_big_object some_detail;
        mutable std::mutex m;
    public:
        X(some_big_object const& sd) :some_detail(sd) {}

        friend void swap(X& lhs, X& rhs)
        {
            if (&lhs == &rhs)
                return;
            std::lock(lhs.m, rhs.m);
            std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
            std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
            swap(lhs.some_detail, rhs.some_detail);
        }
    };
}
void Concurrency03_06() {

}
