#include "Concurrency06.h" 
#include <exception>
#include <stack>
#include <mutex>
#include <memory>
// 6.设计基于锁的并发数据结构
// 6.1 为并发设计的含义
// 数据结构的线程安全：不会丢失或破坏数据，维持所有不变量，并且没有不确定的竞争条件
// 互斥元(mutex)实现了序列化(serialization)
// 并发设计数据结构的准则：保证存取安全、允许真正的并发存取
// 数据存取安全方面:
// A.保证当数据结构不变性被别的线程破坏时的状态不被任何其它线程看到。
// B.注意避免数据结构接口所固有的竞争现象，通过为完整操作提供函数，而不是提供操作步骤。
// C.注意当出现例外时，数据结构是怎样来保证不变性不被破坏的。
// D.当使用数据结构时，通过限制锁的范围和避免使用嵌套锁，来降低产生死锁的机会。
// 要特别注意构造函数和析构函数，确保构造完成前和析构开始后的独占性；构造函数和析构函数应该是独占的。
// 允许真正并发方面：
// 锁的范围能否被限制，使得一个操作的一部分可以在锁外被执行？
// 数据结构的不同部分时分被不同的互斥元保护？
// 是否所有操作需要同样级别的保护？
// 数据结构的一个小改变能否在不影响操作语义的情况下挺高并发性的机会？
// =======================================================================
// 如何能够最小化必然发生的序列化，并且能够最大限度地实现并发性？
// =======================================================================
// C++17提供了共享互斥量(std::shared_mutex),写独占，读共享。和boost::shared_mutex相同。
namespace {
    // 线程安全栈的类定义
    struct empty_stack : std::exception
    {
        const char* what() const throw()
        {
            return "empty stack";
        }
    };

    template<typename T>
    class threadsafe_stack
    {
    private:
        std::stack<T> data;
        mutable std::mutex m;
    public:
        threadsafe_stack() {}
        threadsafe_stack(const threadsafe_stack& other)
        {
            std::lock_guard<std::mutex> lock(other.m);
            data = other.data;
        }
        threadsafe_stack& operator=(const threadsafe_stack&) = delete;

        void push(T new_value)
        {
            std::lock_guard<std::mutex> lock(m);
            data.push(std::move(new_value)); // ① 可能抛出异常
        }
        std::shared_ptr<T> pop()
        {
            std::lock_guard<std::mutex> lock(m);
            if (data.empty()) throw empty_stack(); // ② 抛出异常时，因为还没作修改，是线程安全的
            std::shared_ptr<T> const res(
                std::make_shared<T>(std::move(data.top()))); // ③ 可能抛出异常，但线程安全
            data.pop(); // ④ 不会抛异常
            return res;
        }
        void pop(T& value)
        {
            std::lock_guard<std::mutex> lock(m);
            if (data.empty()) throw empty_stack();
            value = std::move(data.top()); // ⑤
            data.pop(); // ⑥
        }
        bool empty() const
        {
            std::lock_guard<std::mutex> lock(m);
            return data.empty();
        }
        size_t size() const {
            std::lock_guard<std::mutex> lock(m);
            return data.size();
        }
        // 只有构造函数和析构函数不是线程安全的
    };
}

#include <atomic>
#include <chrono>
#include <thread>
#include <iostream>
void Concurrency06_01() {
    std::cout << "06.01 线程安全栈的类定义" << std::endl;
    threadsafe_stack<int> ts;
    std::atomic_bool stop = false;
    std::thread t1([&]() {
        for (int i = 0; i < 100000; i++) {
            if (!stop) {
                ts.push(i);
            }
        }
        });
    std::thread t2([&]() {
        for (int i = 0; i < 100000; i++) {
            if (!stop) {
                if (ts.empty()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(20));
                }
                else {
                    ts.pop();
                }
            }
        }
        });
    std::thread t3([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        stop.store(true);
        });
    t1.join();
    t2.join();
    t3.join();
    std::cout << "ts.size() = " << ts.size() << std::endl;
}