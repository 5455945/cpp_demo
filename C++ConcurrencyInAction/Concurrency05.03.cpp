#include "Concurrency05.h" 
#include <iostream>
// 5.3.1 synchronizes-with关系
// 5.3.2 happens-before关系
namespace {
    // 一个函数调用的参数的估计顺序是未定义的
    void foo(int num, int a, int b)
    {
        std::cout << a << ", " << b << std::endl;
    }
    int get_num()
    {
        static int i = 0;
        return ++i;
    }
}
void Concurrency05_03() {
    //foo(0, get_num(), get_num()); // 对get_num()的调用是无序的
    // 对于不同的编译器实现，可能是固定的
    for (int i = 0; i < 100; i++) {
        foo(i, get_num(), get_num());
    }
}