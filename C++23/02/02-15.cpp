#include "02-15.h"

#include <memory>

// 15������ʮ�壺onstexpr std::unique_ptr��P2273R3��
// std::unique_ptr����Ҳ֧�ֱ����ڼ����ˣ�������һ��С���ӣ�

constexpr auto fun() {
    auto p = std::make_unique<int>(4);
    return *p;
}

void test02_15_01() {
    constexpr auto i = fun();
    static_assert(4 == i);
}

void test02_15() {
    test02_15_01();
}
