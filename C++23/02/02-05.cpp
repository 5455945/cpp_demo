#include "02-05.h"

#include <type_traits> // std::is_constant_evaluated()
#include <iostream>

// 5�������壺if consteval��P1938��
// �������漰������������immediate function������consteval function��
// ����Ŀ���ǽ��һ���ܼ򵥵����⣬����C++20�У�consteval function���Ե���constexpr function�������������С�

consteval auto bar(int m) {
    return m * 6;
}
/*
constexpr auto foo(int m) {
    return bar(m);
}

void test02_05_01() {
    [[maybe_unused]] auto res = foo(42);
}

// ���ϴ����޷�����ͨ������Ϊconstexpr function������ǿ�Ʊ�֤�ڱ�����ִ�У���������Ȼ�޷�����consteval function��
// ��ʹ�����if std::is_constant_evaluated()��������Ȼ�޷�����ɹ�

constexpr auto foo2(int m) {
    if (std::is_constant_evaluated()) {
        return bar(m);
    }
    return 42;
}

void test02_05_02() {
    [[maybe_unused]] auto res = foo2(42);
}
*/
// �������һ�����⣬P1938�����ͨ��if consteval���޸�������⡣��C++23�У���������д��
constexpr auto foo3(int m) {
    // msvc ��֧�� if constevel
    //if consteval {
    //    return bar(m);
    //}
    return 42;
}
void test02_05_03() {
    [[maybe_unused]] auto res = foo3(2);
    std::cout << "res=" << res << std::endl;
}

// Ŀǰ��GCC 12��Clang 14�����ϰ汾�Ѿ�ʵ���˸����ԡ�

void test02_05() {
    //test02_05_01();
    //test02_05_02();
    test02_05_03();
}
