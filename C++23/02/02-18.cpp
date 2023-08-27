#include "02-18.h"

#include <iostream> // std::cin
#include <utility> // std::unreachable()

// 18、特性十八：std::unreachable（P0627R6）
// 在某些情况下，我们可以确定某个位置是不可能被执行到的，但编译器却无法识别这个情况。
// 这时，我们可以使用std::unreachable来告诉编译器，从而避免不必要的运行期检查。
// 下面是一个简单的例子：

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
