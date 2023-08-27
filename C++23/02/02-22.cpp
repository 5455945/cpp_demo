#include "02-22.h"

#include <algorithm> // std::clamp
#include <cmath> // std::isfinite

// 22、特性二十二：Attributes（P1774R8, P2173R1, P2156R1）
// 在C++23中，Attributes也有一些改变。
// 首先，P1774引入了一个新的Attribute [[assume]] 。实际上，在许多编译器中，类似的特性已经存在，
// 例如MSVC和ICC使用__assume()，Clang使用__builtin_assume()。由于GCC没有类似的特性，
// 因此它是最早实现标准 [[assume]] 的编译器之一。目前，只有GCC 13支持该特性，该版本预计在四月发布，同时也对Rangs的支持非常完善。
// 现在，我们可以通过宏来使用 [[assume]] ：


#if defined(__clang__)
#define ASSUME(expr) __builtin_assume(expr)
#elif defined(__GNUC__) && !defined(__ICC)
#define ASSUME(expr) if (expr) {} else { __builtin_unreachable(); }
#elif defined(_MSC_VER) || defined(__ICC)
#define ASSUME(expr) __assume(expr)
#endif


// 论文当中的一个例子：

void limiter(float* data, size_t size) {
    ASSUME(size > 0);
    ASSUME(size % 32 == 0);

    for (size_t i = 0; i < size; ++i) {
        ASSUME(std::isfinite(data[i]));
        data[i] = std::clamp(data[i], -1.0f, 1.0f);
    }
}

void test02_22_01() {
    float data[] = { 2.0f, 2.0f, 3.5f, 4.8f, 6.9f };
    limiter(data, 5);
}
// 第一个是假设size永不为0，总是正数；第二个告诉编译器size总是32的倍数；第三个表明数据不是NaN或无限小数。
// 这些假设不会被评估或检查，编译器会假设它们为真，并根据它们来优化代码。
// 需要注意的是，如果这些假设为假，可能会产生未定义行为（UB）。

// 下面是使用[[assume]]特性和不使用该特性编译产生的指令数对比结果：


// 另外，P2173使得可以在Lambda表达式上使用Attributes。下面是一个例子：
// Any attribute so specified does not appertain to the function 
// call operator or operator template itself, but its type.
//auto lam = [] [[nodiscard]] () ->int { return 42; };

void test02_22_02()
{
    //lam();
}

// Output:
// <source>: In function 'int main()':
// <source>:12:8: warning: ignoring return value of '<lambda()>', declared with attribute 'nodiscard' [-Wunused-result]
//    12 |     lam();
//       |     ~~~^~
// <source>:8:12: note: declared here
//     8 | auto lam = [][[nodiscard]] ->int { return 42; };
//       |            ^


// 需要注意的是，Attributes属于闭包类型（closure type），而不属于operator()。
// 因此，有些Attributes不能使用，比如 [[noreturn]] ，它表明函数的控制流不会返回到调用方，
// 而对于Lambda函数是会返回的。 除此之外，这里还展示了C++的另一个Lambda特性。 在C++23之前，
// 最简单的Lambda表达式为{}，而到了C++23，则是[]{}，可以省略无参时的括号，这要归功于P1102。 
// 早在GCC 9中就已经支持在Lambda表达式上使用Attributes，而Clang 13现在也支持该特性。
// 最后，P2156移除了对重复Attributes的限制。简而言之，两种重复Attributes的语法评判不一致。以下是一个例子：

//// Not allow
//[[nodiscard, nodiscard]] auto foo() {
//    return 42;
//}

// Allowed
[[nodiscard]] [[nodiscard]] auto foo() {
    return 42;
}

// 为了保证标准更加简单和一致，P2156移除了对重复Attributes的限制。 在什么情况下会出现重复Attributes，可以看一下论文中的解释：

// During this discussion, it was brought up that the duplication across attribute-specifiers are 
// to support cases where macros are used to conditionally add attributes to an attribute-specifier-seq, 
// however it is rare for macros to be used to generate attributes within the same attribute-list. 
// Thus, removing the limitation for that reason is unnecessary.

// 在使用宏生成时，可能会出现重复的Attributes，因此允许使用第二种语法。实际上，许多基于宏生成的代码很少使用第一种语法，
// 这就是为什么标准限制这种情况的原因。但是，这种限制并没有让标准更简单。因此，最终移除了该限制。 
// 目前，使用GCC 11和Clang 13+，这两种语法的结果将保持一致。


void test02_22() {
    test02_22_01();
    test02_22_02();
}
