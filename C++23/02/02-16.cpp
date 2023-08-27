#include "02-16.h"

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>  // std::quoted
#include <span> // std::span
#include <cassert>

// 16、特性十六：Improving string and string_view（P1679R3, P2166R1, P1989R2, P1072R10, P2251R1）
// 针对string和string_view，P1679提出了一些增强，其中之一是增加了一个contain()函数，下面是一个小例子：


void test02_16_01() {
    std::string str("dummy text");
    if (str.contains("dummy")) {
        // do something
    }
}

// 目前，GCC 11、Clang 12和MSVC v19.30已经支持该特性。 P2166使得从nullptr构建它们不再产生未定义行为，而是直接导致编译失败。

void test02_16_02() {
    //std::string s{ nullptr };       // error!
    //std::string_view sv{ nullptr }; // error!
}

// 目前，GCC 12、Clang 13和MSVC v19.30已经支持该特性。 P1989是针对std::string_view的，下面是一个小例子：
void test02_16_03() {
    std::vector v{ 'a', 'b', 'c' };
    
    // Before
    std::string_view sv(v.begin(), v.end());
    
    // After
    std::string_view sv23{ v };
}

// 以前无法直接从Ranges构建std::string_view，现在这种方式得到了支持。 
// 该特性已经被GCC 11、Clang 14和MSVC v19.30所支持。
// 针对string，P1072新增了一个成员函数：
// template< class Operation >
// constexpr void resize_and_overwrite(size_type count, Operation op);
// 我们可以通过提案中的一个示例来理解这个特性：

void test02_16_04() {
    std::string s{ "Food: " };

    s.resize_and_overwrite(10, [](char* buf, int n) {
        return std::find(buf, buf + n, ':') - buf;
        });

    std::cout << std::quoted(s) << '\n'; // "Food"
}

// 这个特性主要包括两个操作：改变大小和覆盖内容。第一个参数是新的大小，第二个参数是一个操作符，用于设置新的内容。
// 然后的逻辑是：如果maxsize小于等于s的大小，删除最后的size()-maxsize个元素；如果maxsize大于s的大小，
// 追加maxsize-size()个默认元素；最后调用erase(begin() + op(data(), maxsize), end())。
// 下面提供一个例子，可以使用上述逻辑来理解该函数：

void test02_16_05() {
    constexpr std::string_view fruits[]{ "apple", "banana", "coconut", "date", "elderberry" };
    std::string s1{ "Food: " };

    //s1.resize_and_overwrite(16, [sz = s1.size()](char* buf, std::size_t buf_size) {
    //    const auto to_copy = std::min(buf_size - sz, fruits[1].size()); // 6
    //    std::memcpy(buf + sz, fruits[1].data(), to_copy); // append "banana" to s1.
    //    return sz + to_copy; // 6 + 6
    //    });

    std::cout << s1; // Food: banana
}

#define ASSERT_EQUAL(a, b) assert(a == b)
#define ASSERT(a) assert(a)
void test02_16_06() {
    char input[] = "10 20 30";
    //std::ispanstream is{ std::span<char>{input} };
    //int i;
    //
    //is >> i;
    //ASSERT_EQUAL(10, i);
    //
    //is >> i;
    //ASSERT_EQUAL(20, i);
    //
    //is >> i;
    //ASSERT_EQUAL(30, i);
    //
    //is >> i;
    //ASSERT(!is);
}


void test02_16() {
    test02_16_01();
    test02_16_02();
    test02_16_03();
    test02_16_04();
    test02_16_05();
    test02_16_06();
}
