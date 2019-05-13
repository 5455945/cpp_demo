#include "03-02.h"
#include <iostream>
#include <tuple>

// 3.2 可变参数模板
// 3.2.1 可变参数模板函数
template <class... T>
void func03_02_01(T... args) {
	std::cout << sizeof...(args) << std::endl; // 打印变参个数
}
void test03_02_01() {
	std::cout << __FUNCTION__ << " start" << std::endl;
	func03_02_01();
	func03_02_01(1, 2);
	func03_02_01(1, 2.5, "test");
	std::cout << __FUNCTION__ << " end" << std::endl;
}
// 1递归函数方式展开参数包
// 终止函数
void func03_02_02_print() {
	std::cout << "empty" << std::endl;
}
// 展开函数
template<class T, class ...Args>
void func03_02_02_print(T head, Args... rest) {
	std::cout << "parameters " << head << std::endl;
	func03_02_02_print(rest...);
}
void test03_02_02() {
	std::cout << __FUNCTION__ << " start" << std::endl;
	func03_02_02_print(1, 2, 3, 4);
	std::cout << __FUNCTION__ << " end" << std::endl;
}
//// 递归终止函数也可以写成,最好有两个参数
//template<typename T, typename T1>
//void func03_02_02_print(T t, T1 t1) {
//	std::cout << t << " " << t1 << std::endl;
//}

// 使用type_traits展开参数包
template<std::size_t I = 0, typename Tuple>
typename std::enable_if<I == std::tuple_size<Tuple>::value>::type func03_02_03_printp(Tuple t) { }
template<std::size_t I = 0, typename Tuple>
typename std::enable_if < I <std::tuple_size<Tuple>::value>::type func03_02_03_printp(Tuple t) {
	std::cout << std::get<I>(t) << std::endl;
	func03_02_03_printp<I + 1>(t);
}
template<typename ...Args>
void func03_02_03_print(Args... args) {
	func03_02_03_printp(std::make_tuple(args...));
}
void test03_02_03() {
	std::cout << __FUNCTION__ << " start" << std::endl;
	func03_02_03_print();
	func03_02_03_print(1);
	func03_02_03_print(1, 2, 3, 4, 5);
	std::cout << __FUNCTION__ << " end" << std::endl;
}
// 使用逗号表达式和初始化列表展开参数 1
template<class T>
void func03_02_04_printarg(T t) {
	std::cout << t << std::endl;
}
template<class ...Args>
void func03_02_04_expand(Args... args) {
	int arr[] = { (func03_02_04_printarg(args), 0)... };
}
void test03_02_04() {
	std::cout << __FUNCTION__ << " start" << std::endl;
	//func03_02_04_expand(); // error C2466: 不能分配常量大小为 0 的数组
	func03_02_04_expand(1);
	func03_02_04_expand(1, 2, 3, 4, 5);
	std::cout << __FUNCTION__ << " end" << std::endl;
}
// 使用逗号表达式和初始化列表展开参数 2，使用std::initializer_list
template<class T>
void func03_02_05_printarg(T t) {
	std::cout << t << std::endl;
}
template<class ...Args>
void func03_02_05_expand(Args... args) {
	std::initializer_list<int>{(func03_02_05_printarg(args), 0)... };
}
void test03_02_05() {
	std::cout << __FUNCTION__ << " start" << std::endl;
	func03_02_05_expand();
	func03_02_05_expand(1);
	func03_02_05_expand(1, 2, 3, 4, 5);
	std::cout << __FUNCTION__ << " end" << std::endl;
}
// 使用逗号表达式和初始化列表展开参数 3,使用lambda表达式
template<class ...Args>
void func03_02_06_expand(Args... args) {
	// 在vs2015下，没有输出结果，lambda表达式没有被调用
	std::initializer_list<int>{([&] {std::cout << args << std::endl; }, 0)... };
}
void test03_02_06() {
	std::cout << __FUNCTION__ << " start" << std::endl;
	func03_02_06_expand();
	func03_02_06_expand(1);
	func03_02_06_expand(1, 2, 3, 4, 5);
	std::cout << __FUNCTION__ << " end" << std::endl;
}
void test03_02() {
	test03_02_01();
	test03_02_02();
	test03_02_03();
	test03_02_04();
	test03_02_05();
	test03_02_06();
	return;
}