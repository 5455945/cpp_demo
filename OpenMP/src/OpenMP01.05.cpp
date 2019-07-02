#include "OpenMP01.05.h"
#include "omp.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <array>
#include <numeric>

// OpenMP: OpenMP��һ��ʹ�þ���
// https://blog.csdn.net/Augusdi/article/details/8804161
void test()
{
    int a = 0;
    for (int i = 0; i < 100000000; i++)
        a++;
}
void test01_05_01() {
    clock_t t1 = clock();
    for (int i = 0; i < 8; i++)
        test();
    clock_t t2 = clock();
    std::cout << "time: " << t2 - t1 << std::endl;
}
void test01_05_02() {
    clock_t t1 = clock();
#pragma omp parallel for
    for (int i = 0; i < 8; i++)
        test();
    clock_t t2 = clock();
    std::cout << "time: " << t2 - t1 << std::endl;
}
// ��̬����(race condition)
void test01_05_03_00() {
    int sum = 0;
    int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
#pragma omp parallel for
    for (int i = 0; i < 10; i++)
        sum = sum + a[i];
    std::cout << "sum: " << sum << std::endl;
}
// ������̬����01
void test01_05_03_01() {
    int sum = 0;
    int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
    int coreNum = omp_get_num_procs();//��ô���������
    int* sumArray = new int[coreNum];//��Ӧ������������������һ������
    for (int i = 0; i < coreNum; i++)//�������Ԫ�س�ʼ��Ϊ0
        sumArray[i] = 0;
#pragma omp parallel for
    for (int i = 0; i < 10; i++)
    {
        int k = omp_get_thread_num();//���ÿ���̵߳�ID
        sumArray[k] = sumArray[k] + a[i];
    }
    for (int i = 0; i < coreNum; i++)
        sum = sum + sumArray[i];
    std::cout << "sum: " << sum << std::endl;
}
// ������̬����02
void test01_05_03_02() {
    int sum = 0;
    int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < 10; i++)
        sum = sum + a[i];
    std::cout << "sum: " << sum << std::endl;
}
// ���ٽ���������̬����
void test01_05_04() {
    int max = 0;
    int a[10] = { 11,2,33,49,113,20,321,250,689,16 };
#pragma omp parallel for
    for (int i = 0; i < 10; i++)
    {
        int temp = a[i];
#pragma omp critical 
        {
            if (temp > max)
                max = temp;
        }
    }
    std::cout << "max: " << max << std::endl;
}

// ʹ�þ�����Ϸ�����Բ����
void  CalcPI()
{
    time_t   start, finish, current;
    static   long   num_steps = 10000;
    double   step;
    int   i;
    double   x, pi, sum = 0.0;
    step = 1.0 / (double)num_steps;
    start = clock();
#pragma omp parallel for reduction(+:sum) private(x) //ֻ������һ�䣬��������
    for (i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
        current = clock();
        std::cout << "I = " << i << " " << current - start << std::endl;
    }
    pi = step * sum;
    finish = clock();
    std::cout << "Pi = " << pi << " (" << num_steps << " steps), " << finish - start << "ms/n" << std::endl;
}

// ����forѭ������Ч���Ż�
void test01_05_05() {
    int nthrds = 4;
    omp_set_num_threads(nthrds);
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    long long tPassed = 0;
    for (int i = 0; i < 8; i++) {
        test();
    }
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    auto us_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time01: " << us_duration.count() << std::endl;
    start = std::chrono::system_clock::now();
#pragma omp parallel for   
    for (int i = 0; i < 8; i++) {
        test();
    }
    end = std::chrono::system_clock::now();
    us_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time02: " << us_duration.count() << std::endl;
}

void test01_05_06() {
    std::cout << "Processors Number: " << omp_get_num_procs() << std::endl;

    std::cout << "Parallel area 1" << std::endl;
#pragma omp parallel   
    {
        std::cout << "Threads number: " << omp_get_num_threads() << std::endl;
        std::cout << "; this thread ID is " << omp_get_thread_num() << std::endl;
    }

    std::cout << "Parallel area 2" << std::endl;
#pragma omp parallel   
    {
        std::cout << "Number of threads: " << omp_get_num_threads() << std::endl;
        std::cout << "; this thread ID is " << omp_get_thread_num() << std::endl;
    }
}

void test01_05_07() {
    const int size = 100;
    std::array<int, size> a;
    std::array<int, size> b;
    std::array<int, size> c;
    std::iota(std::begin(a), std::end(a), 1);
    std::iota(std::begin(b), std::end(b), 2);
    std::iota(std::begin(c), std::end(c), 0);
#pragma omp parallel   
    {
#pragma omp for   
        for (int i = 0; i < size; ++i)
        {
            //c[i]ֻ��a[i]��b[i]���   
            c[i] = a[i] + b[i];
        }
    }
    for (auto& it : c) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}

void test01_05_08() {

    //ͨ��private���θñ���֮���ڲ��������ڱ�Ϊ˽�б��������벢��  
    //�����ÿ���߳�ӵ�иñ����Ŀ��������Ҷ������ʼ��  
    int shared_to_private = 1;
#pragma omp parallel for private(shared_to_private)  
    for (int i = 0; i < 10; ++i)
    {
        //std::cout << shared_to_private << std::endl;
    }
    std::cout << __FUNCTION__ << " 01" << std::endl;

    //ͨ��firstprivate���θñ���֮���ڲ��������ڱ�Ϊ˽�б�����  
    //���벢�������ÿ���߳�ӵ�иñ����Ŀ��������һ��ʼ��  
    int share_to_first_private = 1;
#pragma omp parallel for firstprivate(share_to_first_private)  
    for (int i = 0; i < 10; ++i)
    {
        std::cout << ++share_to_first_private << std::endl;
    }
    std::cout << __FUNCTION__ << " 02" << std::endl;

    //ͨ��lastprivate���κ��ڲ��������ڱ�Ϊ˽�б��������벢������  
    //���Ϊ˽�б��������벢�������ÿ���߳�ӵ�иñ����Ŀ��������һ��ʼ��  
    int share_to_last_private = 1;
    std::cout << "Before: " << share_to_last_private << std::endl;
#pragma omp parallel for lastprivate(share_to_last_private) firstprivate(share_to_last_private)  
    for (int i = 0; i < 10; ++i)
    {
        std::cout << ++share_to_last_private << std::endl;
    }
    std::cout << "After: " << share_to_last_private << std::endl;
}

void test01_05_09() {
    int sum = 0;
    std::cout << "Before: " << sum << std::endl;
#pragma omp parallel for shared(sum)  // �����sum�������ݾ���
    for (int i = 0; i < 10; ++i)
    {
        sum += i;
        std::cout << sum << std::endl;
    }
    std::cout << "After: " << sum << std::endl;
}

void test01_05_10() {
    int sum = 0;
    std::cout << "Before: " << sum << std::endl;
#pragma omp parallel for reduction(+:sum)  
    for (int i = 0; i < 10; ++i)
    {
        sum = sum + i;
        std::cout << sum << std::endl;
    }
    std::cout << "After: " << sum << std::endl;
}

void test0105() {
    test01_05_01();
    test01_05_02();
    test01_05_03_00();
    test01_05_03_01();
    test01_05_03_02();
    test01_05_04();
    CalcPI();
    test01_05_05();
    test01_05_06();
    test01_05_07();
    test01_05_08();
    test01_05_09();
    test01_05_10();
}
