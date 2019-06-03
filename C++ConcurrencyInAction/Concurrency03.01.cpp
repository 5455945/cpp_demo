#include "Concurrency03.h"
#include <list>
#include <mutex>
#include <algorithm>
#include <iostream>
// 3 ���̼߳乲������
// 3.1 �̼߳乲�����ݵ�����
// ��������Ĵ���������������[����������ľ�������]��
// ������(invariants),��������(race condition)
// 3.1.1 ��������(race condition)
// ���ǹ�ע����������(problematic)�ľ�������
// ��������(data race):�򵥸�����Ĳ����޸Ķ��������ض����͵ľ������������ݾ�����ɿ��µ�δ������Ϊ(undefined hebavior)
// ������ľ�������ͨ����������Ҫһ���Ե�����޸�2�������ϵ����ݵ����Ρ�
// 3.1.2 ����������ľ�������
// A:�����������ݣ�����ʹ�û���Ԫ(mutex)
// B:�������(lock-free programming)
// C:ʹ���������(transaction):��������ڴ�(software transactional memory,STM)
// 3.2 �û���Ԫ������������
// mutex�ڷ��ʹ�������ǰ����(lock)���ڷ��ʹ�������֮�����(unlock)
// ʹ��mutex�������������:����(deadlock)�����������������ݡ�
// 3.2.1 ʹ��C++�еĻ���Ԫ
// std::mutex,lock(),unlock(),std::lock_guard,std::unique_lock
// ��mutex�����б�
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