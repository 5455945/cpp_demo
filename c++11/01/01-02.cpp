#include "01-02.h"
#include <map>
#include <iostream>
#include <string>

// 1.2 模板的细节改进
// 1.2.1 模板的右尖括号
// 在C++98/03中，模板连续右尖括号会报错
template <typename T>
struct Foo01_02_01 {
	typedef T type;
};
template <typename T>
class A01_02_01 {
	// ...
};
template <int N>
struct Foo01_02_02 {
	// ...
};
void test01_02_01() {
	Foo01_02_01<A01_02_01<int>>::type xx1; // 在C++98/03标准中编译出错，C++11中正常

	//// 在C++11后会错误；error C2143: 语法错误: 缺少“;”(在“>”的前面)；error C2059: 语法错误:“>”
	//Foo01_02_02 < 100 >> 2 > xx2;

	// 使用括号明确语义
	Foo01_02_02 < (100 >> 2) > xx3;
	(xx1); // 消除警告C4101,warning C4101: “xx1”: 未引用的局部变量
	(xx3); // 消除警告C4101
}

// 1.2.2模板别名
typedef unsigned int uint_t;
void func01_02_01(unsigned int) {};
// void func01_02_02(uint_t) {}; // error C2084: 函数“void func(unsigned int)”已有主体

// 如何把下面两个定义用类似一个类型代替？
typedef std::map<std::string, int> map_int_t;
typedef std::map<std::string, std::string>map_str_t;
// C++98/03标准
template <typename Val>
struct str_map { // 外敷类型
	typedef std::map<std::string, Val > type;
	// ...
};
str_map<int>::type map1;
str_map<std::string>::type map2;
// C++11标准，模板别名
template <typename Val>
using str_map_t = std::map<std::string, Val>;
str_map_t<int> map3;
str_map_t<std::string> map4;

// 重定义 unsinged int
typedef unsigned int uint_t;
using uint_t = unsigned int;
// 重定义std::map
typedef std::map<std::string, int> map_int_t;
using map_int_t = std::map<std::string, int>;

// 函数别名
typedef void(*func_t01)(int, int);
using func_t02 = void(*)(int, int);

// C++98/03
template <typename T>
struct func_t03 {
	typedef void(*type)(T, T);
};
// 使用func_t模板
func_t03<int>::type funct03_xx1;

// C++11
template <typename T>
using func_t04 = void(*)(T, T);
// 使用函数模板
func_t04<int> funct04_xx2;

// 1.2.3 函数模板的默认模板参数
template <typename T, typename U = int, U N = 0>
struct Foo01_02_04 {
	T a;
	U b;
};
template <typename T = int> // C++98/03中不允许，C++11可以
void func01_02_02(void) {
	std::cout << "func01_02_02" << std::endl;
}
template <typename R = int, typename U>
R func01_02_03(U val) {
	std::cout << "func01_02_03: " << val << std::endl;
	return val;
}
void test01_02_02() {
	Foo01_02_04<int> x1{ 1, 2 };
	func01_02_02();
	func01_02_03(123);
	auto r1 = func01_02_03<long>(123);
	std::cout << typeid(r1).name() << std::endl;
}
// 默认参数,默认参数类型，类型自动推导；有点复杂
template <typename T>
struct identity {
	typedef T type;
};
template <typename T = int>
void func01_02_04(typename identity<T>::type a, T b = 0) {
    std::cout << __FUNCTION__ << " " << typeid(T).name() << " a=" << a << ", b=" << b << std::endl;
}
void test01_02_03() {
	func01_02_04(123);
	func01_02_04(123, 123.1);
}
void test02() {
	test01_02_01();
	test01_02_02();
	test01_02_03();
	return;
}