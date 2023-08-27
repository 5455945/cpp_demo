#include "02-06.h"

// 6、特性六：Formatted Output（P2093）
// 该提案指的是std::print()，之前已经提到过，这里再简单说明一下。
//
// 标准的cout设计非常糟糕，主要表现在可用性差、基本没有格式化能力、会多次调用格式化I / O函数、
// 默认会同步标准C导致性能低、内容由参数交替组成，在多线程环境下会导致内容错乱显示、二进制占用空间大等问题。
//
// 为了解决这些问题，引入了Formatting Library并在C++20中加入了已在fmt库中使用多年的fmt::print()，
// 以满足可用性、Unicode编码支持、良好的性能和较小的二进制占用空间等要求。
//
// 为了不影响现有代码，该特性专门添加了一个新的头文件，其中包含两个主要函数。

#include <print>

void test02_06_01() {
    const char* world = "world";
    std::print("Hello {}", world);   // doesn't print a newline
    std::println("Hello {}", world); // print a newline
}

// std::print对于cout来说简直是致命的打击，它的易用性和性能远远超过了cout。
// std::print的语法就是Formatting Library的格式化语法，可以参考Using C++20 Formatting Library。性能方面的对比如下：

/*
```
----------------------------------------------------------
Benchmark                Time             CPU   Iterations
----------------------------------------------------------
printf                87.0 ns         86.9 ns      7834009
ostream                255 ns          255 ns      2746434
print                 78.4 ns         78.3 ns      9095989
print_cout            89.4 ns         89.4 ns      7702973
print_cout_sync       91.5 ns         91.4 ns      7903889
```
*/

// 测试结果显示，printf和print的执行速度几乎是cout的三倍，print默认会将输出打印到stdout。
// 当将输出打印到cout并同步标准C的流时（print_cout_sync），print的速度大概比cout快14% ；
// 当不同步标准C的流时（print_cout），速度仍然要快得多。


void test02_06() {
    test02_06_01();
}