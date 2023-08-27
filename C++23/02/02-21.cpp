#include "02-21.h"

#include <stacktrace>
#include <iostream>
#include <memory_resource>

// 21�����Զ�ʮһ��std::stacktrace��P0881R7, P2301R1��
// λ�ڵ������ǰ������ǲ������ջ����Ϣ���Ա���õض�λ��������֪���ĸ����������˵�ǰ������
// �ĸ����������������쳣�ȡ�������һ���򵥵�ʾ����

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


// ��Ҫע����ǣ�Ŀǰֻ��GCC 12.1��MSVC v19.34֧�ָ����ԡ����ʹ��GCC���룬
// ��Ҫ���"-lstdc++_libbacktrace"������ ���⣬std::stacktrace��std::basic_stacktrace��ʹ��Ĭ�Ϸ�����ʱ�ı������䶨�����£�
// using stacktrace = std::basic_stacktrace<std::allocator<std::stacktrace_entry>>;

// ��P2301������Ϊ�������PMR�汾�ı���������Ϊ��
// namespace pmr {
//     using stacktrace =
//         std::basic_stacktrace<std::pmr::polymorphic_allocator<std::stacktrace_entry>>;
// }

//��ˣ�ʹ��std::stacktrace����ӷ��㡣

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
