#include "02-21.h"

#include <stacktrace>
#include <iostream>
#include <memory_resource>

// 21、特性二十一：std::stacktrace（P0881R7, P2301R1）
// 位于的作用是帮助我们捕获调用栈的信息，以便更好地定位错误，例如知道哪个函数调用了当前函数，
// 哪个函数调用引发了异常等。以下是一个简单的示例：

void foo() {
    auto trace = std::stacktrace::current();
    std::cout << std::to_string(trace) << '\n';
}

void test02_21_01() {
    foo();
}

//0 > D:\git\mygit\cpp_demo\C++23\02\02 - 21.cpp(11) : c__23_demo02!foo + 0x46
//1 > D:\git\mygit\cpp_demo\C++23\02\02 - 21.cpp(17) : c__23_demo02!test02_21_01 + 0xB
//2 > D:\git\mygit\cpp_demo\C++23\02\02 - 21.cpp(21) : c__23_demo02!test02_21 + 0xB
//3 > D:\git\mygit\cpp_demo\C++23\02\02 - main.cpp(56) : c__23_demo02!main + 0xC5
//4 > D:\a\_work\1\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl(79) : c__23_demo02!invoke_main + 0x39
//5 > D:\a\_work\1\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl(288) : c__23_demo02!__scrt_common_main_seh + 0x12E
//6 > D:\a\_work\1\s\src\vctools\crt\vcstartup\src\startup\exe_common.inl(331) : c__23_demo02!__scrt_common_main + 0xE
//7 > D:\a\_work\1\s\src\vctools\crt\vcstartup\src\startup\exe_main.cpp(17) : c__23_demo02!mainCRTStartup + 0xE
//8 > KERNEL32!BaseThreadInitThunk + 0x1D
//9 > ntdll!RtlUserThreadStart + 0x28


// 需要注意的是，目前只有GCC 12.1和MSVC v19.34支持该特性。如果使用GCC编译，
// 需要添加"-lstdc++_libbacktrace"参数。 此外，std::stacktrace是std::basic_stacktrace在使用默认分配器时的别名，其定义如下：
// using stacktrace = std::basic_stacktrace<std::allocator<std::stacktrace_entry>>;

// 而P2301，则是为其添加了PMR版本的别名，定义为：
// namespace pmr {
//     using stacktrace =
//         std::basic_stacktrace<std::pmr::polymorphic_allocator<std::stacktrace_entry>>;
// }

//因此，使用std::stacktrace会更加方便。

// Before
void test02_21_02() {
    char buffer[1024];

    std::pmr::monotonic_buffer_resource pool{
        std::data(buffer), std::size(buffer) };

    std::basic_stacktrace<
        std::pmr::polymorphic_allocator<std::stacktrace_entry>>
        trace{ &pool };
}


// After
void test02_21_03() {
    char buffer[1024];

    std::pmr::monotonic_buffer_resource pool{
        std::data(buffer), std::size(buffer) };

    std::pmr::stacktrace trace{ &pool };
}

void test02_21() {
    test02_21_01();
    test02_21_02();
    test02_21_03();
}
