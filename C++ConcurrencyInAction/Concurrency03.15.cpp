#include "Concurrency03.h"
#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <functional>
#include <chrono>
#include <string>
// 类 scoped_lock 是提供便利 RAII 风格机制的互斥包装器，它在作用域块的存在期间占有一或多个互斥。
// 创建 scoped_lock 对象时，它试图取得给定互斥的所有权。控制离开创建 scoped_lock 对象的作用域时，
// 析构 scoped_lock 并以逆序释放互斥。若给出数个互斥，则使用免死锁算法，如同以 std::lock 。
// scoped_lock 类不可复制。
// 以下示例用 std::scoped_lock 锁定互斥对而不死锁，且为 RAII 风格。
namespace {


    struct Employee {
        Employee(std::string id) : id(id) {}
        std::string id;
        std::vector<std::string> lunch_partners;
        std::mutex m;
        std::string output() const
        {
            std::string ret = "Employee " + id + " has lunch partners: ";
            for (const auto& partner : lunch_partners)
                ret += partner + " ";
            return ret;
        }
    };

    void send_mail(Employee &, Employee &)
    {
        // 模拟耗时的发信操作
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    void assign_lunch_partner(Employee &e1, Employee &e2)
    {
        static std::mutex io_mutex;
        {
            std::lock_guard<std::mutex> lk(io_mutex);
            std::cout << e1.id << " and " << e2.id << " are waiting for locks" << std::endl;
        }

        {
            // 用 std::scoped_lock 取得二个锁，而无需担心
            // 其他对 assign_lunch_partner 的调用死锁我们
            // 而且它亦提供便利的 RAII 风格机制
            //std::scoped_lock lock(e1.m, e2.m); // 这个语法在C++17中已经删除

            // 等价代码 1 （用 std::lock 和 std::lock_guard ）
             std::lock(e1.m, e2.m);
             std::lock_guard<std::mutex> lk1(e1.m, std::adopt_lock);
             std::lock_guard<std::mutex> lk2(e2.m, std::adopt_lock);

            // 等价代码 2 （若需要 unique_lock ，例如对于条件变量）
            // std::unique_lock<std::mutex> lk1(e1.m, std::defer_lock);
            // std::unique_lock<std::mutex> lk2(e2.m, std::defer_lock);
            // std::lock(lk1, lk2);
            {
                std::lock_guard<std::mutex> lk(io_mutex);
                std::cout << e1.id << " and " << e2.id << " got locks" << std::endl;
            }
            e1.lunch_partners.push_back(e2.id);
            e2.lunch_partners.push_back(e1.id);
        }

        send_mail(e1, e2);
        send_mail(e2, e1);
    }
}
void Concurrency03_15() {
    Employee alice("alice"), bob("bob"), christina("christina"), dave("dave");

    // 在并行线程中指派，因为就午餐指派发邮件消耗很长时间
    std::vector<std::thread> threads;
    threads.emplace_back(assign_lunch_partner, std::ref(alice), std::ref(bob));
    threads.emplace_back(assign_lunch_partner, std::ref(christina), std::ref(bob));
    threads.emplace_back(assign_lunch_partner, std::ref(christina), std::ref(alice));
    threads.emplace_back(assign_lunch_partner, std::ref(dave), std::ref(bob));

    for (auto &thread : threads) thread.join();
    std::cout << alice.output() << '\n' << bob.output() << '\n'
        << christina.output() << '\n' << dave.output() << '\n';
}