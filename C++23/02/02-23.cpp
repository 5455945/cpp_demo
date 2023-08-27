#include "02-23.h"

// 23�����Զ�ʮ����Lambdas��P1102R2, P2036R3, P2173R1��
// Lambdas���ʽ��C++23��������һЩ�µ����ԡ� ���磬֧��Attributes��ʡ��()�����Ѿ���ǰ���Attributes���ֽ��ܹ�������׸����

// ��һ����������P2036������������ǽ���Ҫ�������� �����Ըı���trailing return types��Name Lookup����
// ΪʲôҪ�ı��أ������ǿ�һ�����ӣ�

void test02_23_01() {
    double j = 42.0;
    // ...
    auto counter = [j = 0]() mutable -> decltype(j) {
        return j++;
        };
}


// ���գ�counter��������double��������int�� ���۲����б��д���ʲôֵ��trailing return type��Name Lookup��������ҵ����� 
// ����ζ�ţ���������д�����ǻ�������ģ�

void test02_23_02() {
    //auto counter = [j = 0]() mutable -> decltype(j) {
    //    return j++;
    //    };

    // Output:
    // <source>:6:44: error: use of undeclared identifier 'j'
    // auto counter = [j=0]() mutable -> decltype(j) {
    //   
}

// ԭ���Ƕ���trailing return type��˵�������������������б��еı���j�� ��������ӿ��Ը�������չʾ�������

void test02_23_03() {
    //template <typename T> int bar(int&, T&&);        // #1
    //template <typename T> void bar(int const&, T&&); // #2
    //
    //int i;
    //auto f = [=](auto&& x) -> decltype(bar(i, x)) {
    //    return bar(i, x);
    //    }
    //
    //f(42); // error
}


// ��C++23�У�trailing return types��Name Lookup�����Ѿ����ı䣺���ⲿ����֮ǰ���Ȳ��Ҳ����б��еı������Ӷ�����������⡣

void test02_23() {
    test02_23_01();
    test02_23_02();
    test02_23_03();
}
