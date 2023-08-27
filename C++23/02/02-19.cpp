#include "02-19.h"

#include <type_traits> // std::underlying_type_t
#include <print> // std::print

// 19、特性十九：std::to_underlying（P1682R3）
// 同样可以在头文件中找到的是std::type_identity，它可以用于推导出某个表达式的潜在类型，相当于以下代码的语法糖：
// static_cast<std::underlying_type_t<Enum>>(e);
// 举个简单的案例：

void print_day(int a) {
    std::print("{}\n", a);
}

enum class Day : std::uint8_t {
    Monday = 1,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};


void test02_19_01() {
    // Before
    print_day(static_cast<std::underlying_type_t<Day>>(Day::Monday));

    // C++23
    print_day(std::to_underlying(Day::Friday));
}

void test02_19() {
    test02_19_01();
}
