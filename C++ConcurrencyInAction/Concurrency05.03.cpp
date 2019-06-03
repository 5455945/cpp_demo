#include "Concurrency05.h" 
#include <iostream>
// 5.3.1 synchronizes-with关系
// 5.3.2 happens-before关系
namespace {
    // 一个函数调用的参数的估计顺序是未定义的
    void foo(int a, int b)
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
    foo(get_num(), get_num()); // 对get_num()的调用是无序的
}