// https://zh.cppreference.com/w/cpp/thread/jthread/jthread
#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include "jthread.hpp" // https://github.com/josuttis/jthread/tree/master/source

void f1(int n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 1 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void f2(int& n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 2 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

class foo
{
public:
    void bar()
    {
        for (int i = 0; i < 5; ++i) {
            std::cout << "Thread 3 executing\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    int n = 0;
};

class baz
{
public:
    void operator()()
    {
        for (int i = 0; i < 5; ++i) {
            std::cout << "Thread 4 executing\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    int n = 0;
};

void test_jthread_cppreference01()
{
    int n = 0;
    foo f;
    baz b;
    std::jthread t0; // t0 不是线程
    std::jthread t1(f1, n + 1); // 按值传递
    std::jthread t2a(f2, std::ref(n)); // 按引用传递
    std::jthread t2b(std::move(t2a)); // t2b 现在运行 f2() 。 t2a 不再是线程
    std::jthread t3(&foo::bar, &f); // t3 在对象 f 上运行 foo::bar()
    std::jthread t4(b); // t4 在对象 b 上运行 baz::operator()
    t1.join();
    t2b.join();
    t3.join();
    std::cout << "Final value of n is " << n << '\n';
    std::cout << "Final value of foo::n is " << f.n << '\n';
    // t4 在析构时结合
}
