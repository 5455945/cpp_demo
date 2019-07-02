#include "OpenMP01.04.h"
#include "omp.h"
#include <iostream>

// 微软官网OpenMP介绍
// https://docs.microsoft.com/zh-cn/cpp/parallel/openmp/openmp-in-visual-cpp?view=vs-2019
// https://docs.microsoft.com/en-us/cpp/parallel/openmp/openmp-in-visual-cpp?view=vs-2019
// Visual Studio 2019 现在还提供了单指令多数据功能。
// openmp的宏: _OPENMP
// 指令格式:#pragma omp directive-name  [clause[ [,] clause]...] new-line

// https://docs.microsoft.com/zh-cn/cpp/parallel/openmp/a-examples?view=vs-2019

// A.1 并行的一个简单循环
void test01_04_01() {
    const int count = 100;
    int a[count] = { 0 };
    double b[count] = { 0 };
#pragma omp parallel for
    for (int i = 1; i < count; i++)
        b[i] = (a[i] + a[i - 1]) / 2.0;
}
// A.2 条件编译
void test01_04_02() {
# ifdef _OPENMP
    std::cout << R"(Compiled by an OpenMP-compliant implementation.)" << std::endl;
# endif

# if defined(_OPENMP) && defined(VERBOSE)
    std::cout << R"(Compiled by an OpenMP-compliant implementation.)" << std::endl;
# endif
}
// A.3 并行区域
void test01_04_03() {
    int x = 25;
    int npoints = 66;
    int iam = 0;
    int np = 8;
    double ipoints = 1;
#pragma omp parallel shared(x, npoints) private(iam, np, ipoints)
    {
        iam = omp_get_thread_num();
        np = omp_get_num_threads();
        ipoints = npoints / np;
        //subdomain(x, iam, ipoints);
        auto f = [&]() {
            std::cout << x << iam << ipoints << std::endl;
        };
        f();
    }
}
// A.4 nowait 子句
void test01_04_04() {
    const int count = 100;
    int const m = 100;
    double a[count] = { 0 };
    double b[count] = { 0 };
    double y[m] = { 2 };
    double z[m] = { 1 };
#pragma omp parallel
    {
#pragma omp for nowait
        for (int i = 1; i < count; i++)
            b[i] = (a[i] + a[i - 1]) / 2.0;
#pragma omp for nowait
        for (int i = 0; i < m; i++)
            y[i] = sqrt(z[i]);
    }
}
void test0104() {
    test01_04_01();
    test01_04_02();
    test01_04_03();
    test01_04_04();
}