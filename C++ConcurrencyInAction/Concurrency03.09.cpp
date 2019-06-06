#include "Concurrency03.h"
#include <mutex>
// 3.2.6 ��std::unique_lock�������
namespace {
    // �ڽ���������ʹ��std::lock/std::lock_guard
    // std::adopt_lock/std::defer_lock��ʹ��
    // std::unique_lock��std::lock_guard���;
    // std::unique_lock���������ӳ�����ʱ/��������Ȩ��Ҫ��һ��������ת�Ƶ�����һ��������ʱ��
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
            std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);// std::defer_lock��������Ԫlhs.mΪδ����
            std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);// std::defer_lock��������Ԫrhs.mΪδ����
            std::lock(lock_a, lock_b); // ����Ԫlock_a/lock_b(lhs.m/rhs.m)�����ﱻ����
            swap(lhs.some_detail, rhs.some_detail);
        }
    };
}
void Concurrency03_09() {
    some_big_object sbo1, sbo2;
    X x1(sbo1), x2(sbo2);
    swap(x1, x2);
}
