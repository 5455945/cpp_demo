#include "C++11.07.h"
#include <iostream>
// 7.1 指针空值 nullptr
// 7.1.1 指针控制，从0到NULL，再到nullptr
// 7.1.2 nullptr和nullptr_t

namespace {
    // 代码清单7-17
    // [captrue] (parameters) mutble ->return-type {statement}
    int Test_7_17() {
        int girls = 3, boys = 4;
        auto totalChild = [](int x, int y)->int {
            return x + y;
        };
        return totalChild(girls, boys);
    }

    // 代码清单7-18
    // 各种lambda表达式
    void Test_7_18() {
        // lambda定义
        auto simple = [] {};  // 最简单的lambda表达式，什么也不做
        int a = 3, b = 4;
        [=] { return a + b; };  // 省略了参数列表和返回类型，返回类型由编译器推断为 int
        auto func1 = [&](int c) { b = a + c; };  // 省略了返回类型，无返回类型
        auto func2 = [=, &b](int c)->int { return b += a + c; };  // 各部分都很完整的lambda表达式

        // lambda执行
        simple();
        auto xx = (b);    // 没啥问题
        auto x = (a, b);  // 这个是哪个的定义，[=] { return a + b; };吗？
        // auto y = func1(9);  // 错误，无返回类型
        func1(9);
        auto z = func2(10);
    }

    // 代码清单7-19
    int Test_7_19() {
        int girls = 3, boys = 4;
        auto totalChild = [girls, &boys]()->int {
            return girls + boys;
        };
        return totalChild();
    }

    // 代码清单7-20
    int Test_7_20() {
        int girls = 3, boys = 4;
        auto totalChild = [=]()->int {
            return girls + boys;
        };
        return totalChild();
    }

    // 代码清单7-21
    class _functor {
    public:
        int operator() (int x, int y) { return x + y; };
    };

    int Test_7_21() {
        int girls = 3, boys = 4;
        _functor totalChild;
        return totalChild(girls, boys);
    }

    // 带状态的仿函数
    class Tax {
    private:
        float rate;
        int base;
    public:
        Tax(float r, int b) : rate(r), base(b) {}
        float operator()(float money) { return (money - base) * rate; }
    };
    void Test_7_22_0() {
        Tax high(0.4f, 30000);
        Tax middle(0.25, 20000);
        std::cout << "Tax over 3w: " << high(37500) << std::endl;
        std::cout << "Tax over 2w: " << middle(27500) << std::endl;
    }

    // 代码清单7-22
    class AirportPrice {
    private:
        float _duttyfreerate;
    public:
        AirportPrice(float rate) : _duttyfreerate(rate) {}
        float operator()(float price) { return price * (1 - _duttyfreerate / 100); }
    };
    void Test_7_22() {
        float tax_price = 5.5f;
        AirportPrice Changi(tax_price);
        auto Changi2 = [tax_price](float price)->float { return price * (1 - tax_price / 100); };
        float purchased = Changi(3699);
        float purchased2 = Changi2(2899);
    }

    // 代码清单7-23
    int z = 5;
    float c = 6;
    void Calc(int&, int, float&, float) {};

    //extern int z;
    //extern float c;
    //void Calc(int&, int, float&, float) ;
    void TestCalc() {
        int x, y = 3;
        float a, b = 4.0;
        int success = 0;
        auto validate = [&]()->bool {
            if ((x == y + z) && (a == b + c)) {
                return 1;
            }
            else {
                return 0;
            }
        };
        Calc(x, y, a, b);
        success += validate();
        y = 1024;
        b = 1e13f;
        Calc(x, y, a, b);
        success += validate();
    };
    void Test_7_23() {
        TestCalc();
    }
};

void Test_C11_07() {
    // 7.3 lambda函数
    // 7.3.1 lambda的一些历史
    // 7.3.2 C++中的lambda函数
    // 代码清单7-17
    int nRet = Test_7_17();

    // 各种lambda表达式
    Test_7_18();

    Test_7_19();

    Test_7_20();

    // 7.3.3 lambda与仿函数
    Test_7_21();

    Test_7_22_0();

    Test_7_22();

    // 7.3.4 lambda的基础使用
    Test_7_23();
}
