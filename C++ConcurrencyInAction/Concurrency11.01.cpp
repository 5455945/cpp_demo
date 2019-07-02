#include "Concurrency11.h"
#include <atomic>
#include <thread>
#include <vector>
#include <iostream>
#include <cassert>

void add1(std::atomic<int>& sum, int count)
{
    for (int j = 0; j < count; ++j)
        sum++;
}
void add2(int& sum, int count)
{
    for (int j = 0; j < count; ++j)
        sum++;
}

void test11_01_01() { // sum使用原子变量
    std::atomic<int> sum = 0;
    const int count = 10000;
    const int n = 10;
    std::vector<std::thread> workers;
    std::cout << "start " << n << " workers, "
        << "every woker inc " << count << " times" << std::endl;

    for (int j = 0; j < n; ++j)
        workers.push_back(std::move(std::thread(add1, std::ref(sum), count)));

    for (auto & w : workers)
        w.join();

    std::cout << "workers end "
        << "finally sum is " << sum << std::endl;

    if (sum == n * count)
        std::cout << "sum++ test passed!" << std::endl;
    else
        std::cout << "sum++ test failed!" << std::endl;
}

void test11_01_02() { // sum使用普通变量
    int sum = 0;
    int count = 10000;
    const int n = 10;
    std::vector<std::thread> workers;
    std::cout << "start " << n << " workers, "
        << "every woker inc " << count << " times" << std::endl;

    for (int j = 0; j < n; ++j)
        workers.push_back(std::move(std::thread(add2, std::ref(sum), count)));

    for (auto & w : workers)
        w.join();

    std::cout << "workers end "
        << "finally sum is " << sum << std::endl;

    if (sum == n * count)
        std::cout << "sum++ test passed!" << std::endl;
    else
        std::cout << "sum++ test failed!" << std::endl;
}

void test11_01_03() {
    const int times = 100000;
    // 测试times次
    for (int i = 0; i < times; i++) {
        int a = 0;
        bool b = false;
        int c = 0;
        std::atomic<bool> flag = false;
        std::atomic<bool> run_flag = false;

        std::thread t1([&]() {
            if (!run_flag) {
                std::this_thread::yield();
            }
            a = 1;
            flag.store(true, std::memory_order_release);
            std::this_thread::yield();
            if (true == flag.load(std::memory_order_acquire)) {
                assert(c != 2); // 大部分情况!=2,很少的情况会发生==2
                //assert(b == false);
            }
            });
        std::thread t2([&]() {
            if (!run_flag) {
                std::this_thread::yield();
            }
            b = true;
            c = 2;
            while (!flag.compare_exchange_weak(b, false, std::memory_order_acq_rel)) { b = true; }
            assert(a == 1);
            });
        run_flag = true;
        t1.join();
        t2.join();
    }
}

void Concurrency11_01() {
    test11_01_01();
    test11_01_02();
    test11_01_03();
}