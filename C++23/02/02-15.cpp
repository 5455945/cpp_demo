#include "02-15.h"

#include <memory>

// 15、特性十五：onstexpr std::unique_ptr（P2273R3）
// std::unique_ptr现在也支持编译期计算了，下面是一个小例子：

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
