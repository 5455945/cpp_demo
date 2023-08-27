#include "02-08.h"

//  8、特性八：import std（P2465）
//  C++20模块的使用存在一定难度，这也是因为标准库中没有提供模块的实现。
// 因此，这个特性的加入符合自然趋势。 现在，我们可以编写如下代码：

// This will set the VS configuration property C/C++->Language->C++ Language Standard to /std:c++latest. 
// Visual Studio 17.6 now also provides a property C/C++->Language->Build ISO C++23 Standard Library Modules which by default is set to Yes 
// and will automatically build the standard library modules on /std:c++latest as part of your project build. 
// So no special handling is required anymore.
// 
// [属性]==>[C/C++]==>[语言]==>[生成 ISO C++23 标准库模块]=是

import std;

void test02_08_01() {
    std::print("Hello standard library modules!\n");
}

// //以下是性能对比：
// 
// ```
// || #include needed headers | Import needed headers | import std | #include all headers | Import allheaders|
// |:--| : --| : --| : --| : --| : --|
// |"Hello world"(<iostream>) | 0.87s | 0.32s | 0.08s | 3.42s | 0.62s|
// |"Mix"(9 headers) | 0.20s | 0.77s | 0.44s | 3.53s | 0.99s |
// ```
// 如果你正在使用混合的C和C++代码，那么可以使用std.compat模块，该模块将包含所有的C函数和标准库函数。
// 目前，该特性几乎没有得到编译器的支持。

void test02_08() {
    test02_08_01();
}