#include "Concurrency03.h"
#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <functional>
#include <chrono>
#include <string>
// �� scoped_lock ���ṩ���� RAII �����ƵĻ����װ���������������Ĵ����ڼ�ռ��һ�������⡣
// ���� scoped_lock ����ʱ������ͼȡ�ø������������Ȩ�������뿪���� scoped_lock �����������ʱ��
// ���� scoped_lock ���������ͷŻ��⡣�������������⣬��ʹ���������㷨����ͬ�� std::lock ��
// scoped_lock �಻�ɸ��ơ�
// ����ʾ���� std::scoped_lock ��������Զ�����������Ϊ RAII ���
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
        // ģ���ʱ�ķ��Ų���
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
            // �� std::scoped_lock ȡ�ö������������赣��
            // ������ assign_lunch_partner �ĵ�����������
            // ���������ṩ������ RAII ������
            //std::scoped_lock lock(e1.m, e2.m); // ����﷨��C++17���Ѿ�ɾ��

            // �ȼ۴��� 1 ���� std::lock �� std::lock_guard ��
             std::lock(e1.m, e2.m);
             std::lock_guard<std::mutex> lk1(e1.m, std::adopt_lock);
             std::lock_guard<std::mutex> lk2(e2.m, std::adopt_lock);

            // �ȼ۴��� 2 ������Ҫ unique_lock �������������������
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

    // �ڲ����߳���ָ�ɣ���Ϊ�����ָ�ɷ��ʼ����ĺܳ�ʱ��
    std::vector<std::thread> threads;
    threads.emplace_back(assign_lunch_partner, std::ref(alice), std::ref(bob));
    threads.emplace_back(assign_lunch_partner, std::ref(christina), std::ref(bob));
    threads.emplace_back(assign_lunch_partner, std::ref(christina), std::ref(alice));
    threads.emplace_back(assign_lunch_partner, std::ref(dave), std::ref(bob));

    for (auto &thread : threads) thread.join();
    std::cout << alice.output() << '\n' << bob.output() << '\n'
        << christina.output() << '\n' << dave.output() << '\n';
}