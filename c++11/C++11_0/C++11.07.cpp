#include "C++11.07.h"
#include <iostream>
// 7.1 ָ���ֵ nullptr
// 7.1.1 ָ����ƣ���0��NULL���ٵ�nullptr
// 7.1.2 nullptr��nullptr_t

namespace {
    // �����嵥7-17
    // [captrue] (parameters) mutble ->return-type {statement}
    int Test_7_17() {
        int girls = 3, boys = 4;
        auto totalChild = [](int x, int y)->int {
            return x + y;
        };
        return totalChild(girls, boys);
    }

    // �����嵥7-18
    // ����lambda���ʽ
    void Test_7_18() {
        // lambda����
        auto simple = [] {};  // ��򵥵�lambda���ʽ��ʲôҲ����
        int a = 3, b = 4;
        [=] { return a + b; };  // ʡ���˲����б�ͷ������ͣ����������ɱ������ƶ�Ϊ int
        auto func1 = [&](int c) { b = a + c; };  // ʡ���˷������ͣ��޷�������
        auto func2 = [=, &b](int c)->int { return b += a + c; };  // �����ֶ���������lambda���ʽ

        // lambdaִ��
        simple();
        auto xx = (b);    // ûɶ����
        auto x = (a, b);  // ������ĸ��Ķ��壬[=] { return a + b; };��
        // auto y = func1(9);  // �����޷�������
        func1(9);
        auto z = func2(10);
    }

    // �����嵥7-19
    int Test_7_19() {
        int girls = 3, boys = 4;
        auto totalChild = [girls, &boys]()->int {
            return girls + boys;
        };
        return totalChild();
    }

    // �����嵥7-20
    int Test_7_20() {
        int girls = 3, boys = 4;
        auto totalChild = [=]()->int {
            return girls + boys;
        };
        return totalChild();
    }

    // �����嵥7-21
    class _functor {
    public:
        int operator() (int x, int y) { return x + y; };
    };

    int Test_7_21() {
        int girls = 3, boys = 4;
        _functor totalChild;
        return totalChild(girls, boys);
    }

    // ��״̬�ķº���
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

    // �����嵥7-22
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

    // �����嵥7-23
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
    // 7.3 lambda����
    // 7.3.1 lambda��һЩ��ʷ
    // 7.3.2 C++�е�lambda����
    // �����嵥7-17
    int nRet = Test_7_17();

    // ����lambda���ʽ
    Test_7_18();

    Test_7_19();

    Test_7_20();

    // 7.3.3 lambda��º���
    Test_7_21();

    Test_7_22_0();

    Test_7_22();

    // 7.3.4 lambda�Ļ���ʹ��
    Test_7_23();
}
