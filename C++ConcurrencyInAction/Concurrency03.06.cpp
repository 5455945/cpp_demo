#include "Concurrency03.h"
#include <mutex>
// 3.2.4 ����:����ͽ��
// ����(deadlock):�������������mutex,�˴˻���ȴ��Է��ͷ��Լ���Ҫ����
// Ϊ�˱��������������Ľ�����ʼ��ʹ����ͬ��˳����������������;�����������л������Ķ��󽻻�ʱ��Ҳ���ܷ���������
// C++��׼���е�std::lock���Խ��ͬʱ������������������
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
