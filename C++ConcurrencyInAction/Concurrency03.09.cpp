#include "Concurrency03.h"
#include <mutex>
// 3.2.6 用std::unique_lock灵活锁定
namespace {
    // 在交换操作中使用std::lock/std::lock_guard
    // std::adopt_lock/std::defer_lock的使用
    // std::unique_lock比std::lock_guard灵活;
    // std::unique_lock适用于在延迟锁定时/锁的所有权需要从一个作用域转移到另外一个作用域时。
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
            std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);// std::defer_lock保留互斥元lhs.m为未锁定
            std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);// std::defer_lock保留互斥元rhs.m为未锁定
            std::lock(lock_a, lock_b); // 互斥元lock_a/lock_b(lhs.m/rhs.m)在这里被锁定
            swap(lhs.some_detail, rhs.some_detail);
        }
    };
}
void Concurrency03_09() {
    some_big_object sbo1, sbo2;
    X x1(sbo1), x2(sbo2);
    swap(x1, x2);
}
