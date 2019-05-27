#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <cstdio>
#include <atomic>
#include <thread>
#include <map>
#include "C++11.02.h"
#include "C++11.03.h"
#include "C++11.04.h"
#include "C++11.05.h"
#include "C++11.06.h"
#include "C++11.07.h"

#if __cplusplus < 199711L
//#if __cplusplus < 201103L
#error "请使用支持C++11的编译器"
#endif

// C++11的新关键字
// alignas
// 

// vs2013不支持noexcept
//void TestNoExcept() noexcept{
//    return ;
//}
#define CONCAT(x)  PRAGMA(test on #x)
#define PRAGMA(x) __pragma(#x)
#define log(...) printf(__VA_ARGS__);

using namespace std;

atomic_llong g_reulst{ 0 };

int main(int argc, char** argv) {
    // 类型别名
    using si = int;
    si n = 5;
    std::cout << n << std::endl;

    // 命名空间别名
    namespace newname = std;
    newname::cout << n << newname::endl;

    // 空指针类型，取消NULL是整数的二义性
    const int *pNULL = nullptr;

    //constexpr 用于定义编译时可计算的常量表达式。
    // 1、编译时常量函数，编译器可以可以计算该函数的值。比如一些宏（macro）函数，就可以用 constexpr 函数来更好的代替。
    // 2、编译时常量数据，比如某些在类和类模板中定义的静态常量数据，以前是用 static const 定义，
    // 现在可以改用 constexpr 定义了，可以获得更好的效率和安全性。
    // VS2013不支持
    // constexpr int *q = nullptr;

    // 容器对象初始化
    std::vector<int> ivec = { 1, 2, 3, 4 };
    std::vector<std::string> svec = { "red", "green", "blue" };

    // auto
    auto adder = [](int op1, int op2) { return op1 + op2; };
    auto adder1 = [](std::string op1, std::string op2) { return op1 + op2; };

    // vs2013不支持参数推导
    // auto adder = [](auto op1, auto op2){ return op1 + op2; };

    std::cout << "int result : "
        << std::accumulate(ivec.begin(),
            ivec.end(),
            0,
            adder)
        << "\n";
    std::cout << "string result : "
        << std::accumulate(svec.begin(),
            svec.end(),
            std::string(""),
            adder1)
        << "\n";

    //std::cout << __func__ << std::endl;
    std::cout << __FUNCTION__ << std::endl;
    //__pragma(12345);
    log("log: %s %d %s\n", __FUNCTION__, __LINE__, __FILE__);

    std::wstring wstr = L"你好a";
    std::string str = "ttttt";

    int i = 7;
    printf_s("i = 7 i++ = %d", i++);

    //static_assert(__cplusplus >= 201103L, "必须使用支持C++11的编译器，才支持该代码");
    Test_C11_02();
    Test_C11_03();
    Test_C11_04();
    Test_C11_05();
    Test_C11_06();
    Test_C11_07();
    return 0;
}
