#include "02-05.h"

#include <type_traits> // std::is_constant_evaluated()
#include <iostream>

// 5、特性五：if consteval（P1938）
// 该特性涉及到立即函数（immediate function），即consteval function。
// 它的目的是解决一个很简单的问题，即在C++20中，consteval function可以调用constexpr function，但反过来不行。

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

// 以上代码无法编译通过，因为constexpr function并不能强制保证在编译期执行，在其中自然无法调用consteval function。
// 即使添加了if std::is_constant_evaluated()，代码仍然无法编译成功

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
// 这里存在一个问题，P1938提出了通过if consteval来修复这个问题。在C++23中，可以这样写：
constexpr auto foo3(int m) {
    // msvc 不支持 if constevel
    //if consteval {
    //    return bar(m);
    //}
    return 42;
}
void test02_05_03() {
    [[maybe_unused]] auto res = foo3(2);
    std::cout << "res=" << res << std::endl;
}

// 目前，GCC 12和Clang 14及以上版本已经实现了该特性。

void test02_05() {
    //test02_05_01();
    //test02_05_02();
    test02_05_03();
}
