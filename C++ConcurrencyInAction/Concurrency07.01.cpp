#include "Concurrency07.h" 
#include <atomic>
// 7 ��������Ĳ������ݽṹ
// 7.1 ����ͽ��
// ����(blocking):ʹ�û���Ԫ������������future��ͬ�����ݵ��㷨�����ݽṹ����Ϊ�������㷨�����ݽṹ��
// ��Щ�⺯���ĵ����������ģ�(����������ʽ����send��ֻ��send��ɲŷ��أ���������÷�����ģʽ�����ú󼴷���)
// ������(nonblocking):�����������⺯�������ݽṹ���㷨����Ϊ�������ġ�
// �����������ݽṹ��һ����������(lock-free)��
// 7.1.1 ���������ݽṹ������
// 7.1.2 �������ݽṹ
// 7.1.3 �޵ȴ����ݽṹ(����ʵ��)
// 7.1.4 �������ݽṹ���ŵ���ȱ��
// ʹ���������ݽṹ����Ҫԭ����Ϊ��:ʵ�����̶ȵĲ���;�ڶ���ԭ����:��׳�ԡ�
// �������������������п���һ���̱߳������������ڿ��Լ���ǰ�ȴ�����һ���߳���ɡ�
// ����Ԫ����Ŀ�ľ���ͨ������Ԫ����ֹ������
// ʹ���������ݽṹʱ��ĳЩ�߳�һ������ִ�в�����
// ʹ���޵ȴ����ݽṹʱ�����ܱ���߳�����ʲô������ÿ���̶߳����Լ���ִ�ж�����Ҫ�ȴ���(����ʵ��)
// �������ݽṹ���ᷢ�����������п��ܴ��ڻ�����
// �����������߳��޸����ݽṹ��ÿ���̵߳��޸Ķ���Ҫ����һ�̵߳Ĳ�������ִ�У��˴˶���һ��ѭ���ͳ��ԡ�
//(����ĳ���߳��ȵ���[ͨ��Э�顢ͨ�����졢����ȫ������])
// ����һ���Ƕ��ݵģ����ή������
// �������޵ȴ����ݽṹ��ȱ��:���ܽ�������(����ƹ�һ���)����Ƹ��ӡ�
namespace {
    // ʹ��std::atomic_flag����������Ԫ��ʵ��
    // ������(spin_lock);ʹ���������������������ݵĴ����Ƿ������ġ����ǲ���������
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
            std::cout << " *" << x << "* "; // *��=���㿴�������
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
            std::cout << " =" << x << "= "; // *��=���㿴�������
            sm.unlock();
        }
        });
    flag.store(true);
    t1.join();
    t2.join();
}
