#include "C++11.02.h"
#include <iostream>
#include <string>
using namespace std;

// 第二章 保证稳定性和兼容性

// 2.1 保持与C99的兼容性
// C99中的预定义宏
// 2.1.1 __func__预定义标识符
// 2.1.2 _Pragma 操作符
// 2.1.3 不带参数宏定义 及 __VA_ARGS__
// 2.1.4 宽窄字符串连接

// 代码清单2-1
void Test_2_1() {
    //std::cout << "standard clib: " << __STDC_HOSTED__ << std::endl;
    //std::cout << "standard c: " << __STDC__ << std::endl;
    //std::cout << "c standard version: " << __STDC_VERSION__ << std::endl;
    //std::cout << "sio/iec: " << STDC_SIO_10646__ << std::endl;
}

// 代码清单2-2
// 在vs2013中，__func__是未声明的标识符
//const char* hello2015() { return __func__; }
//const char* world2015() { return __func__; }
const char* hello() { return __FUNCTION__; }
const char* world() { return __FUNCTION__; }
void Test_2_2() {
    cout << hello() << ", " << world() << endl;
}

// 代码清单2-3
struct TestStruct {
    TestStruct() : name(__FUNCTION__) {};
    const char* name;
};
void Test_2_3() {
    TestStruct ts;
    cout << ts.name << endl;
}

//// 作为函数参数的默认值是不予许的
//void FuncFail(string func_name = __FUNCTION__) {};
//void FuncFail2015(string func_name = __func__) {};

// 2.2 longlong 整型

// 2.3 扩展的整型

// 2.4 __cplusplus

// 2.5 静态断言 static_assert

// 2.6 noexcept修饰符和noexcept操作符

// 2.7 快速初始化成员变量

// 2.8 非静态成员的sizeof

// 2.9 扩展的friend语法

// 2.10 final / override

// 2.11 模板函数的默认模板参数

// 2.12 外部模板

// 2.13 局部和匿名类型做模板参数

// 


void Test_C11_02() {
    Test_2_1();
    Test_2_2();
    Test_2_3();
    int n = 5;
}
