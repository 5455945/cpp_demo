#include "Concurrency03.h"
#include <list>
#include <mutex>
#include <algorithm>
#include <iostream>
// 3 在线程间共享数据
// 3.1 线程间共享数据的问题
// 并发程序的大量复杂性来自于[避免有问题的竞争条件]。
// 不变量(invariants),竞争条件(race condition)
// 3.1.1 竞争条件(race condition)
// 我们关注的是有问题(problematic)的竞争条件
// 竞争数据(data race):因单个对象的并发修改而产生的特定类型的竞争条件，数据竞争造成可怕的未定义行为(undefined hebavior)
// 有问题的竞争条件通常发生在需要一次性的完成修改2个或以上的数据的情形。
// 3.1.2 避免有问题的竞争条件
// A:保护共享数据，比如使用互斥元(mutex)
// B:无锁编程(lock-free programming)
// C:使用事务机制(transaction):软件事务内存(software transactional memory,STM)
// 3.2 用互斥元保护共享数据
// mutex在访问共享数据前锁定(lock)，在访问共享数据之后解锁(unlock)
// 使用mutex可能引入的问题:死锁(deadlock)、保护过多或过少数据。
// 3.2.1 使用C++中的互斥元
// std::mutex,lock(),unlock(),std::lock_guard,std::unique_lock
// 用mutex保护列表
namespace {
    std::list<int> some_list;
    std::mutex some_mutex;

    void add_to_list(int new_value)
    {
        std::lock_guard<std::mutex> guard(some_mutex);
        some_list.push_back(new_value);
    }
    bool list_contains(int value_to_find)
    {
        std::lock_guard<std::mutex> guard(some_mutex);
        return std::find(some_list.begin(), some_list.end(), value_to_find)
            != some_list.end();
    }
}

void Concurrency03_01() {
    add_to_list(42);
    std::cout << "contains(1)=" << list_contains(1) << ", contains(42)=" << list_contains(42) << std::endl;
}