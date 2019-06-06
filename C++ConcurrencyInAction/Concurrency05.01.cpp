#include "Concurrency05.h" 
#include <atomic>
#include <iostream>
#include <cassert>
// 5 C++�ڴ�ģ�ͺ�ԭ�������ϲ���
// 5.1 �ڴ�ģ�ͻ���
// 5.1.1 ������ڴ�ģ��
// 5.1.2 �����ڴ�λ���Լ�����
// ����̷߳�����ͬ���ڴ�λ��(������һ��д����)����������������
// Ϊ�˱��⾺��������������һ��ǿ�Ƶ�˳�򡣻�������ԭ�Ӳ����ܹ����Ʋ�ͬ�̶߳�ͬһ�ڴ�λ�õķ���˳��
// 5.1.3 �޸�˳��(modification order)
// �����ͬ�߳̿�������һ����ͬ��˳��ֵ���ͻ������ݾ�����δ������Ϊ��
// 5.2 C++�е�ԭ�Ӳ���������
// 5.2.1 ��׼ԭ������
// �洢(store)����:���԰���:memory_order_relaxed,memory_order_release,memory_order_seq_cst˳��
// ����(load)����:memory_order_relaxed,memory_order_consume,memory_order_acquire,memory_order_seq_cst
// ��-�޸�-д(read-modify-write)����:memory_order_relaxed,memory_order_consume,memory_order_acquire,
// memory_order_release,memory_order_acq_rel,memory_order_seq_cst
// ���в�����Ĭ��˳����:memory_order_seq_cst
// 5.2.2 std::atomic_flag�ϵĲ���
//test_and_set()����Ϊtrue��������ԭ����ֵ
//clear()������Ϊfalse
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

// ԭ�Ӳ���֧��std::shared_ptr<>
void process_data(std::shared_ptr<int> local) {}
void process_global_data(std::shared_ptr<int> p) {
    std::shared_ptr<int> local = std::atomic_load(&p);
    process_data(local);
}
void update_global_data(std::shared_ptr<int> p) {
    std::shared_ptr<int> local(new int(6));
    std::atomic_store(&p, local);
}
void Concurrency05_01() {
    // x.compare_exchange_weak(y, z);
    // ��ǰֵ������ֵ���ʱ���޸ĵ�ǰֵΪ�趨ֵ������true
    // ��ǰֵ������ֵ����ʱ��������ֵ�޸�Ϊ��ǰֵ������false
    // ԭʼֵ��������ֵҲ���ܴ洢���ɹ�������false����αʧ��(spurious failure),x==yʱ������x=z����ʧ�ܣ�����false��
    // ���ܷ�����ȱ�ٵ����ıȽϲ�����ָ��Ļ����ϣ���ʱ�������޷���֤�ò�����ɣ�
    // -- ������Ϊִ�в������߳��ڱ����ָ�������м䱻�л�������ͬʱ���̶߳��ദ���������Ĳ���ϵͳ�У�������һ���ƻ��е��߳������
    // ��������µ�αʧ��(spurious failure)��ʱ��ĺ��������Ǳ�����ֵ��
    // ��Ϊcompare_exchange_weak��αʧ�ܣ�������ͨ����������ѭ���У�
    //bool expected = false;
    //extern std::atomic<bool> b; // �ڱ�����
    //while (!b.compare_exchange_weak(expected, true) && !expected);
    //����������£�ֻҪexpected��Ϊfalse������compare_exchange_weak()����αʧ�ܣ��ͱ���ѭ����

    // compare_exchange_strong���ᷢ��αʧ��!!!

    std::atomic<int> x = 1;
    int y = 2;
    int z = 3;
    double d = 3.24;
    // ���x=y,x=z;���x!=y,y=x
    bool b = x.compare_exchange_strong(y, z);
    std::cout << b << " " << x << " " << y << " " << z << std::endl;
    x = 0;
    y = 0;
    z = 3;
    b = x.compare_exchange_strong(y, z);
    std::cout << b << " " << x << " " << y << " " << z << std::endl;
    x = 4;
    y = 4;
    z = 5;
    b = x.compare_exchange_strong(y, z);
    std::cout << b << " " << x << " " << y << " " << z << std::endl;
    x = 1;
    y = 2;
    z = 3;
    b = x.compare_exchange_weak(y, z);
    std::cout << b << " " << x << " " << y << " " << z << std::endl;
    x = 4;
    y = 4;
    z = 5;
    b = x.compare_exchange_weak(y, z);
    std::cout << b << " " << x << " " << y << " " << z << std::endl;
    d = 3.24;
    b = x.compare_exchange_weak(y, d);
    std::cout << b << " " << x << " " << y << " " << d << std::endl;
    x = 0;
    y = 0;
    b = x.compare_exchange_weak(y, d);
    std::cout << b << " " << x << " " << y << " " << d << std::endl;
    int e = x.exchange(9);

    std::atomic_flag af = ATOMIC_FLAG_INIT;
    bool b1 = false;
    b1 = af.test_and_set(std::memory_order_acquire); // test_and_set ����ԭ����ֵ�����ú�Ϊtrue
    b1 = af.test_and_set(std::memory_order_release);
    af.clear();
    while (af.test_and_set(std::memory_order_acquire));

    // 5.2.3 ����std::atomic<bool>�Ĳ���
    std::atomic<bool> b2(true);
    if (b2.is_lock_free()) {
        std::cout << "std::atomic<boo> ����������" << std::endl;
    }
    else {
        std::cout << "std::atomic<boo> ��������" << std::endl;
    }
    bool b3 = b2.exchange(false);
    b3 = b2.load();
    
    // 5.2.4 std::atomic<T*>�ϵĲ���:ָ����������
    class Foo {};
    Foo some_array[5];
    std::atomic<Foo*> p(some_array);
    Foo* x4 = p.fetch_add(2); // ��p��2������ԭ����ֵ
    assert(x4 == some_array); // ���ص���ԭֵ��
    assert(p.load() == &some_array[2]); // p�Ѿ���2��
    x4 = (p -=1); // ��p��1�������µ�ֵ
    assert(x4 == &some_array[1]);
    assert(p.load() == &some_array[1]);
    x4 = (p += 1);
    x4 = p.fetch_sub(1);
    assert(x4 == &some_array[2]); // ���ص���ԭֵ
    assert(p.load() == &some_array[1]); // p�Ѿ���1��
    p.fetch_add(3, std::memory_order_release);

    // 5.2.5 ��׼ԭ�����͵Ĳ���
    // load(),store(),exchange(),compare_exchange_weak(), compare_exchange_strong(),
    // fetch_add(), fetch_sub(), fetch_and(), fetch_or(), fetch_xor()

    // 5.2.6 std::atomic<>������ģ��
    // �û���������:UDTʹ��std::atomic<UDT>;���UDT����ʱƽ����
    // ����ʹ��memcpy��memcmp

    // ��������float��doubleʱ��Ӧ��ע��ȽϽ��
    std::atomic<float> f1 = 0.5;
    float f2 = 3.0;
    float f22 = 2.0;
    f1.store(2.0);
    if (f1.compare_exchange_strong(f22, f2)) {
        std::cout << f1.load() << std::endl;
    }

    // 5.2.7 ԭ�Ӳ��������ɺ���
    //���ɺ��������Ϊ�ɼ���C���ԣ��������������������ʹ��ָ����������á�
    std::atomic<bool> ba(true);
    std::atomic_is_lock_free(&ba);
    std::atomic_store(&ba, false);
    std::atomic_store_explicit(&ba, true, std::memory_order_release);
    std::atomic_flag af2 = ATOMIC_FLAG_INIT;
    std::atomic_flag_test_and_set(&af2);
    std::atomic_flag_clear(&af2);
    std::atomic_flag_test_and_set_explicit(&af2, std::memory_order_seq_cst);

    //// C++���ṩ�˶�std::shared_ptr<>��֧��
    //void process_data(std::shared_ptr<int> local) {}
    //void process_global_data(std::shared_ptr<int> p) {
    //    std::shared_ptr<int> local = std::atomic_load(&p);
    //    process_data(local);
    //}
    //void update_global_data(std::shared_ptr<int> p) {
    //    std::shared_ptr<int> local(new int(6));
    //    std::atomic_store(&p, local);
    //}
}