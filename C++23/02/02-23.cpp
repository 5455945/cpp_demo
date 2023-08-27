#include "02-23.h"

// 23、特性二十三：Lambdas（P1102R2, P2036R3, P2173R1）
// Lambdas表达式在C++23中引入了一些新的特性。 例如，支持Attributes和省略()，这已经在前面的Attributes部分介绍过，不再赘述。

// 另一个新特性由P2036提出，下面我们将主要讨论它。 该特性改变了trailing return types的Name Lookup规则。
// 为什么要改变呢？让我们看一个例子：

void test02_23_01() {
    double j = 42.0;
    // ...
    auto counter = [j = 0]() mutable -> decltype(j) {
        return j++;
        };
}


// 最终，counter的类型是double，而不是int。 无论捕获列表中存在什么值，trailing return type的Name Lookup都不会查找到它。 
// 这意味着，仅仅这样写代码是会编译出错的：

void test02_23_02() {
    //auto counter = [j = 0]() mutable -> decltype(j) {
    //    return j++;
    //    };

    // Output:
    // <source>:6:44: error: use of undeclared identifier 'j'
    // auto counter = [j=0]() mutable -> decltype(j) {
    //   
}

// 原因是对于trailing return type来说，它根本看不到捕获列表中的变量j。 下面的例子可以更清晰地展示这个错误：

void test02_23_03() {
    //template <typename T> int bar(int&, T&&);        // #1
    //template <typename T> void bar(int const&, T&&); // #2
    //
    //int i;
    //auto f = [=](auto&& x) -> decltype(bar(i, x)) {
    //    return bar(i, x);
    //    }
    //
    //f(42); // error
}


// 在C++23中，trailing return types的Name Lookup规则已经被改变：在外部查找之前，先查找捕获列表中的变量，从而解决上述问题。

void test02_23() {
    test02_23_01();
    test02_23_02();
    test02_23_03();
}
