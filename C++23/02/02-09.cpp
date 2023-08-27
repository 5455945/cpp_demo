#include "02-09.h"

#include <memory>
#include <print>

// https://en.cppreference.com/w/cpp/memory/inout_ptr_t
// 
// 9、特性九：out_ptr（P1132r8）
// C++23引入了两个新的抽象类型，即std::out_ptr_t和std::inout_ptr_t，以及对应的函数std::out_ptr()和std::inout_ptr()，用于方便地处理指针参数。
// 
// 这些类型和函数主要用于与C API进行交互。以下是一个例子的对比：

// Before
int foreign_resetter(int** params) {
    if (params && *params) {
        return 0;
    }
    return -1;
}

int test02_09_01() {
    auto up = std::make_unique<int>(5);

    int* up_raw = up.release();
    if (int ec = foreign_resetter(&up_raw)) {
        return ec;
    }

    up.reset(up_raw);
    return 0;
}

////////////////////////////////
// After
//int old_c_api2(int**);

int test02_09_02() {
    auto up = std::make_unique<int>(5);

    if (int ec = foreign_resetter(std::inout_ptr(up))) {
        return ec;
    }

    // *up is still valid
    std::println("{}", *up.get());
    return 0;
}


void test02_09() {
    test02_09_01();
    test02_09_02();
}