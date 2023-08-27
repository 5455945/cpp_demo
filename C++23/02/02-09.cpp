#include "02-09.h"

#include <memory>
#include <print>

// https://en.cppreference.com/w/cpp/memory/inout_ptr_t
// 
// 9�����Ծţ�out_ptr��P1132r8��
// C++23�����������µĳ������ͣ���std::out_ptr_t��std::inout_ptr_t���Լ���Ӧ�ĺ���std::out_ptr()��std::inout_ptr()�����ڷ���ش���ָ�������
// 
// ��Щ���ͺͺ�����Ҫ������C API���н�����������һ�����ӵĶԱȣ�

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