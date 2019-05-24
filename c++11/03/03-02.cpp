#include "03-02.h"
#include <iostream>
#include <tuple>
#include <string>

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
// 3.2.2 可变参数模板类
//// tuple就是一个可变参数模板类
//template <class... Types> class tuple;
// 可变参数模板类可以携带任意类型任意个数的参数
std::tuple<int> tp1 = std::make_tuple(1);
std::tuple<int, double> tp2 = std::make_tuple(1, 2.5);
std::tuple<int, double, std::string> tp3 = std::make_tuple(1, 2.5, "");
// 可变参数模板也可以带0个参数
std::tuple<> tp;
// 1.模板递归和特化方式展开参数包(递归+特化)

// A.三段式声明
// 第一部分，前向声明，声明Sum1是一个可变参数模板
template<typename... Args> struct Sum1;
// 第二部分，展开的可变参数模板类，告诉编译期如何递归展开参数包
template<typename First, typename... Rest>
struct Sum1<First, Rest...> {
	enum { value = Sum1<First>::value + Sum1<Rest...>::value };
};
// 第三部分，特化的类终止递归
template<typename Last> // 展开到最后一个参数终止
struct Sum1<Last> {
	enum { value = sizeof(Last) };
};
//// 递归终止函数可以有多种写法
//// 展开到零个参数终止,
//template<> struct Sum1<> { enum { value = 0 }; };
void test03_02_07() {
	std::cout << Sum1<int, double, short>::value << std::endl;
}

// B.两段式声明
template<typename First, typename ...Rest>
struct Sum2 {
	enum { value = Sum2<First>::value + Sum2<Rest...>::value };
};
template<typename Last>
struct Sum2<Last> {
	enum { value = sizeof(Last) };
};
//// 展开到零个参数终止,两段式形式不能到零个参数终止
//template<> struct Sum2<> { enum { value = 0 }; };
void test03_02_08() {
	std::cout << Sum2<int, double, short>::value << std::endl;
}

// 使用std::integral_constant来消除枚举定义value
// 前向声明
template<typename ...Args> struct Sum3;
// 基本定义
template<typename First, typename... Rest>
struct Sum3<First, Rest...> : std::integral_constant<int, Sum3<First>::value + Sum3<Rest...>::value> {};
// 递归终止
template<typename Last>
struct Sum3<Last> : std::integral_constant<int, sizeof(Last)> {};
void test03_02_09() {
	std::cout << Sum3<int, double, short>::value << std::endl;
}

// 2 继承方式展开参数包(继承+特化)
// 整型序列的定义
template<int...> struct IndexSeq1 {};
// 继承方式，开始展开参数包
template<int N, int... Indexes1>
struct MakeIndexes1 : MakeIndexes1<N - 1, N - 1, Indexes1...> {};
// 模板特化，终止展开参数包的条件
template<int... Indexes1>
struct MakeIndexes1<0, Indexes1...> {
	typedef IndexSeq1<Indexes1...> type;
};
void test03_02_10() {
	using T = MakeIndexes1<3>::type;
	std::cout << typeid(T).name() << std::endl;
	// struct IndexSeq1<0,1,2>
}
// 降序方式
// 整型序列的定义
template<int...> struct IndexSeq2 {};
// 继承方式，开始展开参数包
template<int N, int... Indexes2>
struct MakeIndexes2 : MakeIndexes2<N - 1, Indexes2..., N - 1> {}; // 和1比较，调换以下顺序
// 模板特化，终止展开参数包的条件
template<int... Indexes2>
struct MakeIndexes2<0, Indexes2...> {
	typedef IndexSeq2<Indexes2...> type;
};
void test03_02_11() {
	using T = MakeIndexes2<3>::type;
	std::cout << typeid(T).name() << std::endl;
	// struct IndexSeq2<2,1,0>
}
// 用IndexSeq展开并打印可变参数顺序
template<int...> struct IndexSeq3 {};
template<int N, int... Indexes3>
struct MakeIndexes3 {
	// using type = MakeIndexes3<N - 1, N - 1, Indexes3...>::type;
	using type = typename MakeIndexes3<N - 1, N - 1, Indexes3...>::type;
};
template<int... Indexes3>
struct MakeIndexes3<0, Indexes3...> {
	using type = IndexSeq3<Indexes3...>;
};
template<int ...Indexes3, typename ...Args>
void print_helper3(IndexSeq3<Indexes3...>, std::tuple<Args...>&& tup) {
	print3(std::get<Indexes3>(tup)...); // 将tuple转换为函数参数，在调用方法1
}
template<typename ...Args>
void print3(Args... args) {
	print_helper3(typename MakeIndexes3<sizeof...(Args)>::type(), std::make_tuple(args...));
}
void test03_02_12() {
}

// 3.2.3 可变参数模板消除重复代码
// A.C++98/03实现的打印函数
template <typename T>
void Print030213(T t) {
	std::cout << t << std::endl;
}
template <typename T1, typename T2>
void Print030213(T1 t1, T2 t2) {
	std::cout << t1 << " " << t2 << std::endl;
}
template <typename T1, typename T2, typename T3>
void Print030213(T1 t1, T2 t2, T3 t3) {
	std::cout << t1 << " " << t2 << " " << t3 << std::endl;
}
template <typename T1, typename T2, typename T3, typename T4>
void Print030213(T1 t1, T2 t2, T3 t3, T4 t4) {
	std::cout << t1 << " " << t2 << " " << t3 << " " << t4 << std::endl;
}
template <typename T1, typename T2, typename T3, typename T4, typename T5>
void Print030213(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5) {
	std::cout << t1 << " " << t2 << " " << t3 << " " << t4 << " " << t5 << std::endl;
}
// 使用C++11的可变参数模板函数
void Print030213B() { // 终止函数，支持0个参数
}
template <typename T, typename ...Args>
void Print030213B(T t, Args ...args) {
	std::cout << t << " ";
	Print030213B(args...);
}
void test03_02_13() {
	//Print030213();
	Print030213(1, 2.5, "test13");
	Print030213B();
	Print030213B(1, 2.4, "test13B");
}
// 创建对象的抽象工程函数
// C++98/03的方法
template <typename T>
T* Instance() {
	return new T();
}
template <typename T, typename T0>
T* Instance(T0 args0) {
	return new T(args0);
}
template <typename T, typename T0, typename T1>
T* Instance(T0 args0, T1 args1) {
	return new T(args0, args1);
}
template <typename T, typename T0, typename T1, typename T2>
T* Instance(T0 args0, T1 args1, T2 args2) {
	return new T(args0, args1, args2);
}
template <typename T, typename T0, typename T1, typename T2, typename T3>
T* Instance(T0 args0, T1 args1, T2 args2, T3 args3) {
	return new T(args0, args1, args2, args3);
}
template <typename T, typename T0, typename T1, typename T2, typename T3, typename T4>
T* Instance(T0 args0, T1 args1, T2 args2, T3 args3, T4 args4) {
	return new T(args0, args1, args2, args3, args4);
}
// C++11的写法
//template <typename T, typename ... Args>
//T * InstanceC11(Args... args) {  // 值拷贝，存在行呢个损耗
//	return new T(args...);
//};
template<typename T, typename... Args>
T* InstanceC11(Args&&... args) {
	return new T(std::forward<Args>(args)...); // 使用完美转发方式
};
//template<typename T, typename... Args>
//T* Instance(Args&&... args) {
//	return new T(std::forward<Args>(args)...);
//}
void test03_02_14() {
	struct A { A(int) {} };
	struct B { B(int, int) {} };
	A* pa = Instance<A>(1);
	B* pb = Instance<B>(1, 2);
	A* pa11 = InstanceC11<A>(1);
	B* pb11 = InstanceC11<B>(1, 2);
	delete pa;
	delete pb;
	delete pa11;
	delete pb11;
}
void test03_02() {
	test03_02_01();
	test03_02_02();
	test03_02_03();
	test03_02_04();
	test03_02_05();
	test03_02_06();
	test03_02_07();
	test03_02_08();
	test03_02_09();
	test03_02_10();
	test03_02_11();
	test03_02_12();
	test03_02_13();
	test03_02_14();
	return;
}