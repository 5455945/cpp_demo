#include "02-04.h"

// 4、特性四：Multidimensional Arrays（P2128）
// 这个特性用于访问多维数组。以前，C++的operator[]只支持访问单个下标，无法访问多维数组。
// 因此，为了访问多维数组，以前的方法是：
// 重载operator()，然后就可以使用m(1, 2)来访问第1行第2列的元素。但是，这种方法容易与函数调用产生混淆；
// 重载operator[]并使用std::initializer_list作为参数，然后就可以使用m[{1, 2}]来访问元素。但是，这种方法看起来很奇怪；
// 链式链接operator[]，然后就可以使用m[1][2]来访问元素。同样，这种方式也很奇怪。定义一个at()成员函数，然后使用at(1, 2)来访问元素也不太方便。
// C++23终于可以通过m[1, 2]这种方式来访问多维数组了。以下是一个例子：
#include <array>
#include <iostream>
/*
template <class T, size_t R, size_t C>
struct matrix {
    T& operator[](const size_t r, const size_t c) noexcept {
        return data_[r * C + c];
    }

    const T& operator[](const size_t r, const size_t c) const noexcept {
        return data_[r * C + c];
    }

private:
    std::array<T, R* C> data_;
};


void test02_04_01() {
    matrix<int, 2, 2> m;
    m[0, 0] = 0;
    m[0, 1] = 1;
    m[1, 0] = 2;
    m[1, 1] = 3;

    for (auto i = 0; i < 2; ++i) {
        for (auto j = 0; j < 2; ++j) {
            std::cout << m[i, j] << ' ';
        }
        std::cout << std::endl;
    }
}
*/

void test02_04() {
    //test02_04_01();
}