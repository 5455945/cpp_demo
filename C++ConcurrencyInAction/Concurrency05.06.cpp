#include "Concurrency05.h" 
#include <thread>
#include <atomic>
#include <iostream>
namespace {
    // ���̵߳���ɢ����
    std::atomic<int> x(0), y(0), z(0); // ��
    std::atomic<bool> go(false);       // ��
    unsigned const loop_count = 10;
    struct read_values
    {
        int x, y, z;
    };
    read_values values1[loop_count];
    read_values values2[loop_count];
    read_values values3[loop_count];
    read_values values4[loop_count];
    read_values values5[loop_count];
    void increment(std::atomic<int>* var_to_inc, read_values* values)
    {
        while (!go) //  ����ת���ȴ��ź�
            std::this_thread::yield();
        for (unsigned i = 0; i < loop_count; ++i)
        {
            values[i].x = x.load(std::memory_order_relaxed);
            values[i].y = y.load(std::memory_order_relaxed);
            values[i].z = z.load(std::memory_order_relaxed);
            var_to_inc->store(i + 1, std::memory_order_relaxed); // ��
            std::this_thread::yield();
        }
    }
    void read_vals(read_values* values)
    {
        while (!go) // ����ת���ȴ��ź�
            std::this_thread::yield();
        for (unsigned i = 0; i < loop_count; ++i)
        {
            values[i].x = x.load(std::memory_order_relaxed);
            values[i].y = y.load(std::memory_order_relaxed);
            values[i].z = z.load(std::memory_order_relaxed);
            std::this_thread::yield();
        }
    }
    void print(read_values* v)
    {
        for (unsigned i = 0; i < loop_count; ++i)
        {
            if (i)
                std::cout << ",";
            std::cout << "(" << v[i].x << "," << v[i].y << "," << v[i].z << ")";
        }
        std::cout << std::endl;
    }
}
void Concurrency05_06() {
    std::thread t1(increment, &x, values1);
    std::thread t2(increment, &y, values2);
    std::thread t3(increment, &z, values3);
    std::thread t4(read_vals, values4);
    std::thread t5(read_vals, values5);
    go = true; // �޿�ʼִ����ѭ�����ź�
    t5.join();
    t4.join();
    t3.join();
    t2.join();
    t1.join();
    print(values1); // �ߴ�ӡ���յ�ֵ
    print(values2);
    print(values3);
    print(values4);
    print(values5);
}
//   ����������һ���ǳ��򵥵ĳ����������������ȫ��ԭ�ӱ����ٺ�����̣߳�
// ÿ���߳�ѡ��10�Σ���memory_order_relaxed��ȡ����ԭ�ӱ�����ֵ���������
// ���������С��������߳��е�ÿ���߳�ÿ��ͨ��ѭ���ܸ�������һ��ԭ�ӱ�����
// �����������߳�ֻ�Ƕ�ȡ��һ�����е��̶߳������ӣ���ʹ�ӡ��ÿ���̴߳洢��
// �����е�ֵ�ߡ�
//   ԭ�ӱ���go������ȷ�����е��߳̾����ܿ�����ͬ��ʱ�俪ʼѭ��������һ����
// ����һ������Ĳ�������û����ȷ���ӳ٣���һ���̻߳������һ���߳̿�ʼǰ��
// �����ˡ�ÿ���߳��ڽ�����ѭ��֮ǰ�ȴ�go���true�ۡ��ݣ��������е��̶߳���
// ����ʼ��ޣ�go�ű����ó�true��
// 4 �����ɢ˳��
// ǿ�ҽ��������ɢ��ԭ�Ӳ���(memory_order_relaxed),���Ǿ��Ա�Ҫ��
// ������Ա�Ҫ��ҲӦ�ü��������ʹ�á�
