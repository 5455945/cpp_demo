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

// ������ò��󣬻�����Ҫ��������������utf-8
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
	// ֻ�в���idʱ��: ����ʡ�Բ�д
	fmt::print("name:{1}, age: {0:}", 42, "knox");
	// ������ָ������������ַ��ĸ�����
	fmt::print("name:{1}, age: {0:.5}", "1234567890", "knox");
	// �����name:knox, age: 12345

	// c�ַ���������ô���أ�����ַ�����
	fmt::print("name:{1}, age: {0:.5}", "123", "knox");
	// �����name:knox, age: 123

	// �������ִ����ȣ�ֻ�Ը���������
	fmt::print("{:.2f}", 42.0f);
	// �����42.00
	//fmt::print("{:.2f}", 42); ���뱨��
	//fmt::print("{:.2f}", true); ���뱨��
	auto s = fmt::format(std::locale("en_US.UTF-8"), "{:L}", 1234567890);
	fmt::print("{}", s);
	// ����� 1,234,567,890
	// ��Ŵ��㿪ʼ
	fmt::print("{0}, {1}, {2}\n", 'a', 'b', 'c');
	// print: "a, b, c"


	fmt::print("{}, {}, {}\n", 'a', 'b', 'c');
	// print: "a, b, c"

	fmt::print("{2}, {1}, {0} \n", 'a', 'b', 'c');
	// print: "c, b, a"
	// fmt::print("{2}, {1}, {0} {3}\n", 'a', 'b', 'c'); ���뱨��û�е��ĸ�����

	// ���
	// a, b, c  
	// a, b, c  
	// c, b, a  
	// ��ָ��������Ĭ��Ϊ�ո� ��������� <>^ �ͼٶ������Ŷ�������
	fmt::print("{:<30}\n", "left aligned");
	// 
	fmt::print("{:<<30}\n", "left aligned");

	fmt::print("{:>30}\n", "right aligned");
	fmt::print("{:>>30}\n", "right aligned");

	fmt::print("{:^30}\n", "centered");

	fmt::print("{:^^30}\n", "centered");

	// ���
	//left aligned                  
	//left aligned<<<<<<<<<<<<<<<<<<
	//                right aligned 
	//>>>>>>>>>>>>>>>>>right aligned
	//        centered              
	//^^^^^^^^^^^centered^^^^^^^^^^^
	// ���Զ�̬���ÿ�Ⱥ;��ȣ������������ڴˣ�
	// ��̬���ÿ�ȵ�ʱ�򣬿��arg_id Ϊ ����+1�� 
	//           0 1   2 3  ����arg_id ������{ �ĸ�������Ȼ{} һ���ǳɶԳ��ֵġ�
	fmt::print("{:<{}} {:.{}f} \n", "left aligned", 30, 3.14, 1);
	fmt::print("{:.{}f}\n", 3.14, 1);
	// ���
	// left aligned                   3.1  
	// 3.1  

	// + ����������+�ţ�������-��
	fmt::print("{:+f}; {:+f}\n", 3.14, -3.14);
	// �ո������ӿո񣬸�����-��
	fmt::print("{: f}; {: f}\n", 3.14, -3.14);
	// -�Ŵ����������䣬������-�� same as '{:f}; {:f}' �൱����Ĭ����Ϊ
	fmt::print("{:-f}; {:-f}\n", 3.14, -3.14);

	fmt::print("{:+}; {:+}\n", 3, -3);
	fmt::print("{:-}; {:-}\n", 3, -3);
	fmt::print("{: }; {: }\n", 3, -3);
	fmt::print("{:}; {:}\n", 3, -3);

	// ���
	//+3.140000; -3.140000
	// 3.140000; -3.140000
	//3.140000; -3.140000
	//+3; -3
	//3; -3
	// 3; -3
	//3; -3
	// + ����������+�ţ�������-��
	fmt::print("{:+f}; {:+f}\n", 3.14, -3.14);
	// �ո������ӿո񣬸�����-��
	fmt::print("{: f}; {: f}\n", 3.14, -3.14);
	// -�Ŵ����������䣬������-�� same as '{:f}; {:f}' �൱����Ĭ����Ϊ
	fmt::print("{:-f}; {:-f}\n", 3.14, -3.14);

	fmt::print("{:+}; {:+}\n", 3, -3);
	fmt::print("{:-}; {:-}\n", 3, -3);
	fmt::print("{: }; {: }\n", 3, -3);
	fmt::print("{:}; {:}\n", 3, -3);

	// ���
	//+3.140000; -3.140000
	// 3.140000; -3.140000
	//3.140000; -3.140000
	//+3; -3
	//3; -3
	// 3; -3
	//3; -3

	// # ���Ϸ��� 0x 0 0b
	fmt::print("int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}\n", 42);

	fmt::print("int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}\n", 42);

	// #06 ������Ϊ6���� �������ڽ���֮ǰʹ��0��䣬 ����ָ����С������
	fmt::print("int: {0:d};  hex: {0:#06x};  oct: {0:#06o};  bin: {0:#06b}\n", 42);
	fmt::print("int: {0:d};  hex: {0:#01x};  oct: {0:#02o};  bin: {0:#03b}\n", 42);
	// ���
	// int: 42;  hex: 2a;  oct: 52; bin: 101010
	// int: 42;  hex: 0x2a;  oct: 052;  bin: 0b101010
	// int: 42;  hex: 0x002a;  oct: 000052;  bin: 0b101010
	// int: 42;  hex: 0x2a;  oct: 052;  bin: 0b101010

	//fmt::print(
	//	"��{0:��^{2}}��\n"
	//	"��{1: ^{2}}��\n"
	//	"��{0:��^{2}}��\n", "", "Hello, knox!", 20);

	const char* world = "world";
	fmt::print("Hello {}", world); // doesn't print a newline
	fmt::println("Hello {}", world); // print a newline

}
