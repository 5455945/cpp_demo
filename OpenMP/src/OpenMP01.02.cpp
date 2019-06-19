#include "OpenMP01.01.h"
#include "omp.h"
#include <iostream>

// [并行计算] 2. OpenMP简介
// https://blog.csdn.net/magicbean2/article/details/75530667

// [并行计算] 1. 并行计算简介
// https://blog.csdn.net/magicbean2/article/details/75174859

// 编译器指令： 编译器指令在你的源代码中可能被显示为注释，并且被编译器所忽略，除非你明显地告诉编译器——通常情况下是设置适当的编译器标识，
// 这将在 5. OpenMP程序编译 中进行讨论。OpenMP的编译器指令的目标主要有：
// 1）产生一个并行区域；
// 2）划分线程中的代码块；
// 3）在线程之间分配循环迭代；
// 4）序列化代码段；
// 5）同步线程间的工作。

// 编译器指令的语法如下
// sentinel directive-name [clause, ...]
// 例: #pragma omp parallel default(shared) private(beta,pi)

//运行时库函数： OpenMP API中的运行时库函数是不断增长的，其主要目标包括：
// 1）设置和查询线程数；
// 2）查询线程的唯一标识符（ID），线程的祖先标识符，或者线程组的大小等；
// 3）设置和查询动态线程的属性；
// 4）查询是否在并行区域，以及在什么级别的并行区域中；
// 5）设置和查询嵌套并行；
// 6）设置、初始化以及终止锁或者嵌套锁；
// 7）查询挂钟时间和分辨率。
// 环境变量： OpenMP提供了一些环境变量，用来在运行时对并行代码的执行进行控制。
// 这些环境变量可以控制：
// 1）设置线程数；
// 2）指定循环如何划分；
// 3）将线程绑定到处理器；
// 4）启用/禁用嵌套并行，设置最大的嵌套并行级别；
// 5）启用/禁用动态线程；
// 6）设置线程堆栈大小；
// 7）设置线程等待策略。

// 指令有效范围
//静态（词汇）范围：
//代码以本文的方式包含在指令之后的结构化块中；
//指令的静态范围不跨越多个例程或者代码文件。
//孤立指令：
//独立于另一个封装指令的OpenMP指令被称为是一个孤立指令。它存在于另一个指令的静态（词法）范围之外；
//独立指令将跨越例程或者可能的代码文件。
//动态范围：
//指令的动态范围包括其静态（词法）范围以及孤立指令的范围。

//静态扩展：for指令在封闭并行块内发生；
//孤立指令：CRITICAL和SECTIONS指令在封闭并行块外发生；
//动态扩展：CRITICAL和SECTIONS指令在for和PARALLEL指令的动态上下文中发生。

//并行区域构建
//#pragma omp parallel [clause ...]  newline 
//if (scalar_expression)
//private (list)
//shared(list)
//default (shared | none)
//firstprivate(list)
//reduction(operator: list)
//copyin(list)
//num_threads(integer - expression)

// do/for指令
//#pragma omp for [clause ...]  newline 
//schedule(type[, chunk])
//ordered
//private (list)
//firstprivate(list)
//lastprivate(list)
//shared(list)
//reduction(operator: list)
//collapse(n)
//nowait
//for_loop

void test0102_01() {
    int nthreads, tid;
    // Fork a team of threads with each thread having a private tid variable
#pragma omp parallel private(tid)
    {
        // Obtain and print thread id
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

        // Only master thread does this
        if (tid == 0) {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    }  // All threads join master thread and terminate
}

void test0102_02() {
    const int N{ 1000 };
    const int CHUNKSIZE{ 100 };
    int i, chunk;
    double a[N], b[N], c[N];

    // Some initializations
    for (i = 0; i < N; i++)
        a[i] = b[i] = i * 1.0;
    chunk = CHUNKSIZE;

#pragma omp parallel shared(a,b,c,chunk) private(i)
    {
#pragma omp for schedule(dynamic,chunk) nowait
        for (i = 0; i < N; i++)
            c[i] = a[i] + b[i];
    }   // end of parallel region
}

void test0102_03() {
    const int N{ 1000 };
    int i;
    double a[N], b[N], c[N], d[N];

    // Some initializations
    for (i = 0; i < N; i++) {
        a[i] = i * 1.5;
        b[i] = i + 22.35;
    }

#pragma omp parallel shared(a,b,c,d) private(i)
    {
#pragma omp sections nowait
        {
#pragma omp section
            for (i = 0; i < N; i++)
                c[i] = a[i] + b[i];

#pragma omp section
            for (i = 0; i < N; i++)
                d[i] = a[i] * b[i];
        }  // end of sections
    }  // end of parallel region
}

void test0102_04() {
    const int N{ 1000 };
    const int CHUNKSIZE{ 100 };
    int i, chunk;
    double a[N], b[N], c[N];

    // Some initializations
    for (i = 0; i < N; i++)
        a[i] = b[i] = i * 1.0;
    chunk = CHUNKSIZE;

#pragma omp parallel for shared(a,b,c,chunk) private(i) schedule(static,chunk)
    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];
}

void test0102_05() {
    int x = 0;
#pragma omp parallel shared(x) 
    {
#pragma omp critical 
        x = x + 1;
    }  // end of parallel region
}

void test0102_06() {
    int b, tid;
    static int a;
    static double x;
#pragma omp threadprivate(a, x)
    // Explicitly turn off dynamic threads
    omp_set_dynamic(0);
    printf("1st Parallel Region:\n");
#pragma omp parallel private(b,tid)
    {
        tid = omp_get_thread_num();
        a = tid;
        b = tid;
        x = 1.1 * tid + 1.0;
        printf("Thread %d:   a,b,x= %d %d %f\n", tid, a, b, x);
    }  // end of parallel region

    printf("************************************\n");
    printf("Master thread doing serial work here\n");
    printf("************************************\n");

    printf("2nd Parallel Region:\n");
#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        printf("Thread %d:   a,b,x= %d %d %f\n", tid, a, b, x);
    }  // end of parallel region
}

void test0102_07() {
    int i, n, chunk;
    double a[100], b[100], result;

    // Some initializations
    n = 100;
    chunk = 10;
    result = 0.0;
    for (i = 0; i < n; i++) {
        a[i] = i * 1.0;
        b[i] = i * 2.0;
    }

#pragma omp parallel for default(shared) private(i) \
    schedule(static, chunk) reduction(+:result)
    for (i = 0; i < n; i++) {
        result = result + (a[i] * b[i]);
    }
    printf("Final result= %f\n", result);
}

void test0102() {
    test0102_01();
    test0102_02();
    test0102_03();
    test0102_04();
    test0102_05();
    test0102_06();
    test0102_07();
}