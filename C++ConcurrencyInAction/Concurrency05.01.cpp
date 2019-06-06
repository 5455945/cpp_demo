#include "Concurrency05.h" 
#include <atomic>
#include <iostream>
#include <cassert>
// 5 C++内存模型和原子类型上操作
// 5.1 内存模型基础
// 5.1.1 对象和内存模型
// 5.1.2 对象、内存位置以及并发
// 多个线程访问相同的内存位置(至少有一个写操作)，会引起竞争条件；
// 为了避免竞争条件，必须有一个强制的顺序。互斥量和原子操作能够控制不同线程对同一内存位置的访问顺序。
// 5.1.3 修改顺序(modification order)
// 如果不同线程看到的是一个不同的顺序值，就会有数据竞争和未定义行为。
// 5.2 C++中的原子操作及类型
// 5.2.1 标准原子类型
// 存储(store)操作:可以包括:memory_order_relaxed,memory_order_release,memory_order_seq_cst顺序
// 载入(load)操作:memory_order_relaxed,memory_order_consume,memory_order_acquire,memory_order_seq_cst
// 读-修改-写(read-modify-write)操作:memory_order_relaxed,memory_order_consume,memory_order_acquire,
// memory_order_release,memory_order_acq_rel,memory_order_seq_cst
// 所有操作的默认顺序是:memory_order_seq_cst
// 5.2.2 std::atomic_flag上的操作
//test_and_set()设置为true，并返回原来的值
//clear()，设置为false
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

// 原子操作支持std::shared_ptr<>
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
    // 当前值与期望值相等时，修改当前值为设定值，返回true
    // 当前值与期望值不等时，将期望值修改为当前值，返回false
    // 原始值等于期望值也可能存储不成功，返回false；即伪失败(spurious failure),x==y时，可能x=z设置失败，返回false。
    // 可能发生在缺少单个的比较并交换指令的机器上，此时处理器无法保证该操作完成；
    // -- 可能因为执行操作的线程在必须的指令序列中间被切换出来，同时在线程多余处理器数量的操作系统中，它被另一个计划中的线程替代。
    // 这种情况下的伪失败(spurious failure)是时间的函数而不是变量的值。
    // 因为compare_exchange_weak会伪失败，所以它通常必须用在循环中：
    //bool expected = false;
    //extern std::atomic<bool> b; // 在别处设置
    //while (!b.compare_exchange_weak(expected, true) && !expected);
    //在这种情况下，只要expected仍为false，表明compare_exchange_weak()调用伪失败，就保持循环。

    // compare_exchange_strong不会发生伪失败!!!

    std::atomic<int> x = 1;
    int y = 2;
    int z = 3;
    double d = 3.24;
    // 如果x=y,x=z;如果x!=y,y=x
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
    b1 = af.test_and_set(std::memory_order_acquire); // test_and_set 返回原来的值，设置后，为true
    b1 = af.test_and_set(std::memory_order_release);
    af.clear();
    while (af.test_and_set(std::memory_order_acquire));

    // 5.2.3 基于std::atomic<bool>的操作
    std::atomic<bool> b2(true);
    if (b2.is_lock_free()) {
        std::cout << "std::atomic<boo> 是无有锁的" << std::endl;
    }
    else {
        std::cout << "std::atomic<boo> 是有锁的" << std::endl;
    }
    bool b3 = b2.exchange(false);
    b3 = b2.load();
    
    // 5.2.4 std::atomic<T*>上的操作:指针算术运算
    class Foo {};
    Foo some_array[5];
    std::atomic<Foo*> p(some_array);
    Foo* x4 = p.fetch_add(2); // 将p加2并返回原来的值
    assert(x4 == some_array); // 返回的是原值，
    assert(p.load() == &some_array[2]); // p已经加2了
    x4 = (p -=1); // 将p减1并返回新的值
    assert(x4 == &some_array[1]);
    assert(p.load() == &some_array[1]);
    x4 = (p += 1);
    x4 = p.fetch_sub(1);
    assert(x4 == &some_array[2]); // 返回的是原值
    assert(p.load() == &some_array[1]); // p已经减1了
    p.fetch_add(3, std::memory_order_release);

    // 5.2.5 标准原子整型的操作
    // load(),store(),exchange(),compare_exchange_weak(), compare_exchange_strong(),
    // fetch_add(), fetch_sub(), fetch_and(), fetch_or(), fetch_xor()

    // 5.2.6 std::atomic<>初级类模板
    // 用户定义类型:UDT使用std::atomic<UDT>;这个UDT必须时平凡的
    // 可以使用memcpy和memcmp

    // 当类型是float和double时，应该注意比较结果
    std::atomic<float> f1 = 0.5;
    float f2 = 3.0;
    float f22 = 2.0;
    f1.store(2.0);
    if (f1.compare_exchange_strong(f22, f2)) {
        std::cout << f1.load() << std::endl;
    }

    // 5.2.7 原子操作的自由函数
    //自由函数被设计为可兼容C语言，所以它们在所有情况下使用指针而不是引用。
    std::atomic<bool> ba(true);
    std::atomic_is_lock_free(&ba);
    std::atomic_store(&ba, false);
    std::atomic_store_explicit(&ba, true, std::memory_order_release);
    std::atomic_flag af2 = ATOMIC_FLAG_INIT;
    std::atomic_flag_test_and_set(&af2);
    std::atomic_flag_clear(&af2);
    std::atomic_flag_test_and_set_explicit(&af2, std::memory_order_seq_cst);

    //// C++还提供了对std::shared_ptr<>的支持
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