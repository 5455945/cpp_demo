#include "02-18.h"

#include <iostream> // std::cin
#include <utility> // std::unreachable()

// 18������ʮ�ˣ�std::unreachable��P0627R6��
// ��ĳЩ����£����ǿ���ȷ��ĳ��λ���ǲ����ܱ�ִ�е��ģ���������ȴ�޷�ʶ����������
// ��ʱ�����ǿ���ʹ��std::unreachable�����߱��������Ӷ����ⲻ��Ҫ�������ڼ�顣
// ������һ���򵥵����ӣ�

void foo(int a) {
    switch (a) {
    case 1:
        // do something
        break;
    case 2:
        // do something
        break;
    default:
        std::unreachable();
    }
}

bool is_valid(int a) {
    return a == 1 || a == 2;
}

void test02_18_01() {
    int a = 0;
    while (!is_valid(a))
        std::cin >> a;
    foo(a);
}

void test02_18() {
    test02_18_01();
}
