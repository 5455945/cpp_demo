#include "01-01.h"

/*
#include <cstdio>
#include <filesystem>
#include <print>

void test01() {
	std::print("{0} {2}{1}!\n", "Hello", 23, "C++"); // overload (1)

	const auto tmp {std::filesystem::temp_directory_path() / "test.txt"};

	if (std::FILE* stream {std::fopen(tmp.c_str(), "w")})
	{
		std::print(stream, "File: {}", tmp.string()); // overload (2)
		std::fclose(stream);
	}
}*/

//void test01() {}
/*
#include <format>
#include <iostream>
#include <string>
#include <string_view>

template <typename... Args>
std::string dyna_print(std::string_view rt_fmt_str, Args&&... args) {
	return std::vformat(rt_fmt_str, std::make_format_args(args...));
}

void test01() {
	std::cout << std::format("Hello {}!\n", "world");

	std::string fmt;
	for (int i{}; i != 3; ++i) {
		fmt += "{} "; // constructs the formatting string
		std::cout << fmt << " : ";
		std::cout << dyna_print(fmt, "alpha", 'Z', 3.14, "unused");
		std::cout << '\n';
	}
}
*/

// 这个作用不大，还是需要在配置项中设置utf-8
//#pragma execution_character_set("utf-8")
#define FMT_HEADER_ONLY 
//#include "../fmt/include/fmt/core.h"
#include <fmt/core.h>
#include <iostream>

template <typename... Args>
std::string dyna_print(std::string_view rt_fmt_str, Args&&... args) {
	return fmt::vformat(rt_fmt_str, fmt::make_format_args(args...));
}

void test01_01() {
	std::cout << __func__ << " in" << std::endl;
	std::cout << fmt::format("Hello {}!\n", "world");

	std::string fmt;
	for (int i{}; i != 3; ++i) {
		fmt += "{} "; // constructs the formatting string
		std::cout << fmt << " : ";
		std::cout << dyna_print(fmt, "alpha", 'Z', 3.14, "unused");
		std::cout << '\n';
	}
	std::cout << __func__ << " out" << std::endl;
}

void test01() {
	test01_01();
	fmt::print("Hello, world!\n");
	// 只有参数id时候，: 可以省略不写
	fmt::print("name:{1}, age: {0:}", 42, "knox");
	// 非数字指定的是输出的字符的个数。
	fmt::print("name:{1}, age: {0:.5}", "1234567890", "knox");
	// 输出：name:knox, age: 12345

	// c字符串不够怎么办呢，最大字符串长
	fmt::print("name:{1}, age: {0:.5}", "123", "knox");
	// 输出：name:knox, age: 123

	// 对于数字代表精度，只对浮点型有用
	fmt::print("{:.2f}", 42.0f);
	// 输出：42.00
	//fmt::print("{:.2f}", 42); 编译报错
	//fmt::print("{:.2f}", true); 编译报错
	auto s = fmt::format(std::locale("en_US.UTF-8"), "{:L}", 1234567890);
	fmt::print("{}", s);
	// 输出： 1,234,567,890
	// 序号从零开始
	fmt::print("{0}, {1}, {2}\n", 'a', 'b', 'c');
	// print: "a, b, c"


	fmt::print("{}, {}, {}\n", 'a', 'b', 'c');
	// print: "a, b, c"

	fmt::print("{2}, {1}, {0} \n", 'a', 'b', 'c');
	// print: "c, b, a"
	// fmt::print("{2}, {1}, {0} {3}\n", 'a', 'b', 'c'); 编译报错，没有第四个参数

	// 输出
	// a, b, c  
	// a, b, c  
	// c, b, a  
	// 不指定填充符号默认为空格， 如果不存在 <>^ 就假定填充符号都不存在
	fmt::print("{:<30}\n", "left aligned");
	// 
	fmt::print("{:<<30}\n", "left aligned");

	fmt::print("{:>30}\n", "right aligned");
	fmt::print("{:>>30}\n", "right aligned");

	fmt::print("{:^30}\n", "centered");

	fmt::print("{:^^30}\n", "centered");

	// 输出
	//left aligned                  
	//left aligned<<<<<<<<<<<<<<<<<<
	//                right aligned 
	//>>>>>>>>>>>>>>>>>right aligned
	//        centered              
	//^^^^^^^^^^^centered^^^^^^^^^^^
	// 可以动态设置宽度和精度，但仅仅限制于此，
	// 动态设置宽度的时候，宽度arg_id 为 参数+1， 
	//           0 1   2 3  参数arg_id 可以数{ 的个数，当然{} 一定是成对出现的。
	fmt::print("{:<{}} {:.{}f} \n", "left aligned", 30, 3.14, 1);
	fmt::print("{:.{}f}\n", 3.14, 1);
	// 输出
	// left aligned                   3.1  
	// 3.1  

	// + 代表正数加+号，负数加-号
	fmt::print("{:+f}; {:+f}\n", 3.14, -3.14);
	// 空格正数加空格，负数加-号
	fmt::print("{: f}; {: f}\n", 3.14, -3.14);
	// -号代表正数不变，负数加-号 same as '{:f}; {:f}' 相当于是默认行为
	fmt::print("{:-f}; {:-f}\n", 3.14, -3.14);

	fmt::print("{:+}; {:+}\n", 3, -3);
	fmt::print("{:-}; {:-}\n", 3, -3);
	fmt::print("{: }; {: }\n", 3, -3);
	fmt::print("{:}; {:}\n", 3, -3);

	// 输出
	//+3.140000; -3.140000
	// 3.140000; -3.140000
	//3.140000; -3.140000
	//+3; -3
	//3; -3
	// 3; -3
	//3; -3
	// + 代表正数加+号，负数加-号
	fmt::print("{:+f}; {:+f}\n", 3.14, -3.14);
	// 空格正数加空格，负数加-号
	fmt::print("{: f}; {: f}\n", 3.14, -3.14);
	// -号代表正数不变，负数加-号 same as '{:f}; {:f}' 相当于是默认行为
	fmt::print("{:-f}; {:-f}\n", 3.14, -3.14);

	fmt::print("{:+}; {:+}\n", 3, -3);
	fmt::print("{:-}; {:-}\n", 3, -3);
	fmt::print("{: }; {: }\n", 3, -3);
	fmt::print("{:}; {:}\n", 3, -3);

	// 输出
	//+3.140000; -3.140000
	// 3.140000; -3.140000
	//3.140000; -3.140000
	//+3; -3
	//3; -3
	// 3; -3
	//3; -3

	// # 加上符号 0x 0 0b
	fmt::print("int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}\n", 42);

	fmt::print("int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}\n", 42);

	// #06 代表宽度为6个， 不够的在进制之前使用0填充， 超出指定大小被忽略
	fmt::print("int: {0:d};  hex: {0:#06x};  oct: {0:#06o};  bin: {0:#06b}\n", 42);
	fmt::print("int: {0:d};  hex: {0:#01x};  oct: {0:#02o};  bin: {0:#03b}\n", 42);
	// 输出
	// int: 42;  hex: 2a;  oct: 52; bin: 101010
	// int: 42;  hex: 0x2a;  oct: 052;  bin: 0b101010
	// int: 42;  hex: 0x002a;  oct: 000052;  bin: 0b101010
	// int: 42;  hex: 0x2a;  oct: 052;  bin: 0b101010

	//fmt::print(
	//	"┌{0:─^{2}}┐\n"
	//	"│{1: ^{2}}│\n"
	//	"└{0:─^{2}}┘\n", "", "Hello, knox!", 20);

	const char* world = "world";
	fmt::print("Hello {}", world); // doesn't print a newline
	fmt::println("Hello {}", world); // print a newline

}
