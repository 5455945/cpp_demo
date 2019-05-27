#include "C++11.04.h"
#include <iostream>
#include <vector>
#include <type_traits>

using namespace std;

// 消除指定的编译警告
#pragma warning(disable:4101 4305)

// 4.1 右尖括号
template <int i> class X {};
template <typename T> class Y {};

void Test_4_1() {
    Y<X<1> > x1;
    Y<X<2>> x2;
}

void Test_4_2() {
    //X< 1 >> 5 > x3;  // 错误：应输入标识符
    X< (1 >> 5) > x3;
}

// 4.2 auto 类型推导
void Test_4_3() {
    auto name = "world!";
    cout << "hello " << name << endl;
}

// 代码清单4-4
double foo() { return 0.5f; };
void Test_4_4() {
    auto x = 1;
    auto y = foo();
    //struct m { int i;} str;
    //auto str1 = str;  // 编译错误,使用了未初始化变量str
    struct m1 { int i = 0; } str2;
    auto str3 = str2;  // 编译错误,使用了未初始化变量str

    //auto z;  // 无法推导 auto 的类型， z需要初始化
    auto z = x;
}

// 代码清单4-5
void overloop(std::vector<std::string>& vs) {
    std::vector<std::string>::iterator i = vs.begin();
    cout << "vs: ";
    for (; i != vs.end(); ++i) {
        cout << i->c_str() << " ";
    }
    cout << endl;
}
void overloop2(std::vector<std::string>& vs) {
    cout << "vs: ";
    for (std::vector<std::string>::iterator i = vs.begin(); i != vs.end(); ++i) {
        cout << i->c_str() << " ";
    }
    cout << endl;
}

void Test_4_5() {
    std::vector<std::string> vs = { "vs1", "vs2", "vs3", "vs4", "vs5" };
    overloop(vs);
    overloop2(vs);
}

// 代码清单4-6
void overloop1(std::vector<std::string>& vs) {
    cout << "vs: ";
    // 使用auto类型推导，代码会简洁些
    for (auto i = vs.begin(); i != vs.end(); ++i) {
        cout << i->c_str() << " ";
    }
    cout << endl;
}
void Test_4_6() {
    std::vector<std::string> vs = { "vs1", "vs2", "vs3", "vs4", "vs5" };
    overloop1(vs);
}

// 代码清单4-7
class PI {
public:
    double operator*(float v) {
        return (double)val* v;
    }
    const float val = 3.1415927f;
};
void Test_4_7() {
    float radius = 1.7e10;
    PI pi;
    auto circumference = 2 * (pi * radius);

    cout << "circumference: " << circumference << endl;
}

void Test_4_8() {
    unsigned int a = 4294967295;
    unsigned int b = 1;
    auto c = a + b;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "a + b = " << a + b << endl;
}

template <typename T1, typename T2>
double Sum(T1& t1, T2& t2) {
    auto s = t1 + t2;
    return s;
}
void Test_4_9() {
    int a = 3;
    long b = 5;
    float c = 1.0f, d = 5.3f;
    double x = 1.0l;
    auto e = Sum<int, long>(a, b);
    auto f = Sum<float, float>(c, d);
    cout << "e = " << e << ", f = " << f << endl;
}

// vs2013不支持
void Test_4_10() {
#define MAX1(a, b) ((a) > (b)) ? (a) : (b)
    //#define MAX2(a, b) ({ auto _a = (a);  \
    //                     auto _b = (b);  \
    //                     (_a > _b) ? _a : _b; })

    int m = MAX1(1 * 2 * 3 * 4, 5 + 6 + 7 + 8);
    //int n = MAX2(1 * 2 * 3 * 4, 5 + 6 + 7 + 8);
    //cout << "m = " << m << ", n = " << n << endl;
}

// 4.3 decltype

void Test_4_17() {
    int i;
    decltype(i) j = 0;
    cout << typeid(j).name() << endl;

    float a;
    double b;
    decltype(a + b) c;
    cout << typeid(c).name() << endl;
}

// 4.4 追踪返回类型
template <typename T1, typename T2>
auto sum2(T1& t1, T2& t2)->decltype(t1 + t2) {
    return t1 + t2;
}

// 未能使函数模板"unknown-type sum3(T1&, T2&)"专用化
//template <typename T1, typename T2>
//decltype(t1 + t2) sum3(T1& t1, T2& t2) {
//    return t1 + t2;
//}

void Test_4_20_0() {
    int a = 2;
    float b = 3.0f;
    double c = 4.0l;
    auto m = sum2<float, int>(b, a);
    //auto n = sum3<double, int>(c, a);
}

int funcA() {
    cout << "funA : 15" << endl;
    return 15;
}
typedef int(*fpFuncA)();
fpFuncA pfpFuncA = funcA;

fpFuncA getPfpFuncA() {
    return funcA;
}

int(*(*pf())())() {
    //return nullptr;
    return getPfpFuncA;
}

// auto(*)() ->int(*)()  // 一个返回函数指针的函数，假设为a函数
// auto pf1() -> auto(*)() ->int(*)()  // 一个返回a函数指针的函数
auto pf1() -> auto(*)() ->int(*)() {
    //return nullptr;
    return getPfpFuncA;
}
void Test_4_31() {
    cout << is_same<decltype(pf), decltype(pf1)>::value << endl;
    pf1()()();
    pf()()();
}

// 4.5 基于范围的for循环

void Test_C11_04() {
    Test_4_1();
    Test_4_2();
    Test_4_3();
    Test_4_4();
    Test_4_5();
    Test_4_6();
    Test_4_7();
    Test_4_8();
    Test_4_9();
    Test_4_10();
    Test_4_17();
    Test_4_20_0();
    Test_4_31();

    cout << __FUNCTION__ << endl;
}
