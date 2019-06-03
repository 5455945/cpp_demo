#include "Concurrency05.h" 
#include <atomic>
// 5 C++�ڴ�ģ�ͺ�ԭ�������ϲ���
// 5.1 �ڴ�ģ�ͻ���
// 5.1.1 ������ڴ�ģ��
// 5.1.2 �����ڴ�λ���Լ�����
// 5.1.3 �޸�˳��
// 5.2 C++�е�ԭ�Ӳ���������
// 5.2.1 ��׼ԭ������
// 5.2.2 std::atomic_flag�ϵĲ���

namespace {
    // ʹ��std::atomic_flag������������ʵ��
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