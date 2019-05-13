#include "01-01.h"
#include <iostream>
#include <string>

// 1.1 类型推导
// 1.1.1 auto类型推导
// auto在编译时确定待定义变量的类型
// auto修饰的变量必须被初始化，编译器通过初始化来确定auto所代表的类型，即必须要定义变量。
// 1 auto关键字的新意义
void test01_01_01() {
	auto x = 5;  //OK:x是int类型
	auto pi = new auto(1); // OK:pi被推导为int*
	const auto *v = &x, u = 6; // OK:v是const int*类型,u是int类型
	static auto y = 0.0;      // OK:y是double类型
	//const auto *v2 = &x, u2;  // error:虽然v2已经推导出类型，但u2仍然需要写后面的赋值部分。
	//auto int r;   // error:auto不再表示存储类型指示符
	//auto s;       // error:auto无法推导出s的类型
	std::cout << typeid(x).name() << " | " << typeid(pi).name() << " | " << typeid(v).name() << " | "
		<< typeid(u).name() << " | " << typeid(y).name() << std::endl;
	// int | int * __ptr64 | int const * __ptr64 | int | double
	
	std::cout << typeid(x).raw_name() << " | " << typeid(pi).raw_name() << " | " << typeid(v).raw_name() << " | "
		<< typeid(u).raw_name() << " | " << typeid(y).raw_name() << std::endl;
}
// 2 auto的推导规则
void test01_01_02() {
	int x = 0;
	auto* a = &x;
	auto b = &x;
	auto& c = x;
	auto d = c;
	const auto e = x;
	auto f = e;
	const auto& g = x;
	auto& h = g;
	std::cout << typeid(a).name() << " | " << typeid(b).name() << " | " << typeid(c).name() << " | " << typeid(d).name() << " | "
		<< typeid(e).name() << " | " << typeid(f).name() << " | " << typeid(g).name() << " | " << typeid(h).name() << std::endl;
}

// 3 auto的限制
//void func01_01_01(auto a = 1) {}  // error:auto不能用于函数参数
struct Foo {
	//auto var1_ = 0; // error:auto不能用于非静态成员变量
	static const auto var2_ = 0; // OK:var2_->static const int
};
template <typename T>
struct Bar {};
void test01_01_03() {
	int arr[10] = { 0 };
	auto aa = arr; // OK: aa->int*
	//auto rr[10] = arr; // error: auto 类型不能出现在顶级数组中
	//auto rr[10] = { 0， 1， 2， 3 }; // error: auto 无法定义数组
	Bar<int> bar;
	//Bar<auto> bb = bar; // error: auto无法推导出模板参数
	(bar);
}
// 4 什么时候使用auto
#include <map>
// 例1
void test01_01_old1() {
	std::map<double, double> resultMap;
	// ...
	std::map<double, double>::iterator it = resultMap.begin();
	for (; it != resultMap.end(); ++it) {
		// do something
	}
}
// 使用auto
void test01_01_04() {
	std::map<double, double> resultMap;
	// ...
	for (auto it = resultMap.begin(); it != resultMap.end(); ++it) {
		// do something
	}
}
// 例2
#include <unordered_map>
void test01_01_old2() {
	std::unordered_multimap<int, int> resultMap;
	// ...
	std::pair<std::unordered_multimap<int, int>::iterator, std::unordered_multimap<int, int>::iterator> range = resultMap.equal_range(1);
}
void test01_01_05() {
	std::unordered_multimap<int, int> resultMap;
	// ...
	auto range = resultMap.equal_range(1);
}
class Foo01_06 {
public:
	static int get(void) { return 0; }
};
class Bar01_06 {
public:
	static const char* get(void) { return "Bar01_06"; }
};
template<class A01_06>
void func01_06(void){
	auto val = A01_06::get();
    std::cout << val << std::endl;
}
void test01_01_06() {
	func01_06<Foo01_06>();
	func01_06<Bar01_06>();
}

// 1.1.2 decltype关键字
// decltype用来在编译时推导出一个表达式的类型。decltype不会计算表达式的值。
// 1 获知表达式的类型
void test01_01_08() {
	int x = 0;
	decltype(x) y = 1;
	decltype(x + y) z = 0;
	const int &i = x;
	decltype(i) j = y;
	const decltype(z) *p = &z;
	decltype(z) *pi = &z;
	decltype(pi) *pp = &pi;
	std::cout << typeid(y).name() << " | " << typeid(z).name() << " | " << typeid(j).name() << " | " << typeid(p).name() << " | "
		<< typeid(pi).name() << " | " << typeid(pp).name() << std::endl;
	// int | int | int | int const * __ptr64 | int * __ptr64 | int * __ptr64 * __ptr64
}
// 2 decltype的推导规则，decltype(exp)
// 推导规则1，exp是标识符、类访问表达式、decltype(exp)和exp的类型一致
// 推导规则2，exp是函数调用，decltype(exp)和返回值的类型一致
// 推导规则3，其它情况，若exp是一个左值，则decltype(exp)是exp类型的左值引用，否则和exp类型一致
// decltype作用于标识符和类访问表达式示例
class Foo01_09 {
public:
	static const int Number = 0;
	int x;
};
void test01_01_09() {
	int n = 0;
	volatile const int &x = n;
	decltype(n) a = n; // a-> int
	decltype(x) b = n; // b-> const volatile int&
	decltype(Foo01_09::Number) c = 0; // c-> const int
	Foo01_09 foo;
	decltype(foo.x) d = 0; // d-> int,类访问表达式
	(foo);
	std::cout << typeid(a).name() << " | " << typeid(b).name() << " | " << typeid(c).name() << " | " << typeid(d).name() << std::endl;
}
// decltype作用于函数调用的示例
void test01_01_10() {
	const Foo01_09 func_cfoo(void); // 纯右值
	int& func_int_r(void);   // 左值(lvalue,可简单理解为可寻址值)
	int&& func_int_rr(void); // x值(xvalue,右值引用本身是一个xvalue)
	int func_int(void);      // 纯右值(prvalue)
	const int& func_cint_r(void);   // 左值
	const int&& func_cint_rr(void); // x值
	const int func_cint(void);      // 纯右值

	int x = 0;
	decltype(func_int_r())  a1 = x;  // a1-> int&
	decltype(func_int_rr()) b1 = 0;  // b1-> int&&
	decltype(func_int())    c1 = 0;  // c1-> int
	decltype(func_cint_r()) a2 = x;  // a2-> const int&
	decltype(func_cint_rr())b2 = 0;  // b2-> const int&&
	decltype(func_cint())   c2 = 0;  // c2-> int
	decltype(func_cfoo())   ff = Foo01_09(); // ff-> const Foo01_09
	std::cout << typeid(a1).name() << " | " << typeid(b1).name() << " | " << typeid(c1).name() << " | " 
		<< typeid(a2).name() << " | " << typeid(b2).name() << " | " << typeid(c2).name() << " | " 
		<< typeid(ff).name() << std::endl;
	// int | int | int | int | int | int | class Foo01_09
}
// 带括号的表达式和加法运算表达式
void test01_01_11() {
	struct Foo { int x; };
	const Foo foo = Foo();
	decltype(foo.x) a = 0;   // a-> int
	decltype((foo.x)) b = a; // b-> const int&
	int n = 0, m = 0;
	decltype(n + m) c = 0;   // c-> int
	decltype(n += m) d = c;  // d-> int&
	std::cout << typeid(a).name() << " | " << typeid(b).name() << " | " << typeid(c).name() << " | " << typeid(d).name() << std::endl;
	// int | int | int | int
}

// 3 decltype实际应用
// 泛型类型定义可能存在问题的示例
#include <vector>
template<class ContainerT>
class Foo01_01_12 {
	typename ContainerT::iterator it_; // 类型定义可能有问题
public:
	void func(ContainerT& container) {
		it_ = container.begin();
	}
	// ...
};
void test01_01_12() {
	typedef const std::vector<int> container_t;
	container_t arr;
	//Foo01_01_12<container_t> foo; // 当ContainerT是一个const类型时，应当使用const_iterator。
	//foo.func(arr);
}

// 把const类型的容易用模板特化单独处理
#include <vector>
template<class ContainerT>
class Foo01_01_13 {
	typename ContainerT::iterator it_; // 类型定义可能有问题
public:
	void func(ContainerT& container) {
		it_ = container.begin();
	}
	// ...
};
template <class ContainerT>
class Foo01_01_13<const ContainerT>
{
	typename ContainerT::const_iterator it_;
public:
	void func(const ContainerT& container) {
		it_ = container.begin();
	}
	// ...
};
void test01_01_13() {
	typedef const std::vector<int> container_t;
	container_t arr;
	Foo01_01_13<container_t> foo;
	foo.func(arr);
}
// test01_01_12()/test01_01_13()可以使用decltype写成test01_01_14();vs2017下有问题
#include <vector>
template<class ContainerT>
class Foo01_01_14 {
	decltype(ContainerT().begin()) it_;
public:
	void func(ContainerT& container) {
		//std::cout << typeid(it_).name << std::endl;
		it_ = container.begin();
	}
	// ...
};
void test01_01_14() {
	typedef const std::vector<int> container_t;
	container_t arr;
	//Foo01_01_14<container_t> foo;
	//foo.func(arr);
}

//// 标准库中的nullptr_t和size_t的类型定义
//typedef decltype(nullptr) nullptr_t;
//typedef decltype(sizeof(0)) size_t;

// 1.1.3 返回类型后置语法--auto和decltype结合使用
template <typename R, typename T, typename U>
R add01_01(T t, U u) {
	return t + u;
}
void test01_01_15() {
	int a = 1;
	float b = 2.5;
	auto c = add01_01<decltype(a + b)>(a, b);
	std::cout << "test01_01_15: " << c << std::endl;
}
template <typename T, typename U>
decltype(t + u) add01_02(T t, U u) { // error: t,u 尚未定义
	return t + u;
}
template <typename T, typename U>
decltype(T() + U()) add01_03(T t, U u) {
	return t + u;
}
template <typename T, typename U>
decltype((*(T*)0) + (*(U*)0)) add01_04(T t, U u) { // C++03/98下正常
	return t + u;
}
// 明确的C++11返回类型后置语法
template <typename T, typename U>
auto add01_05(T t, U u)->decltype(t + u) {
	return t + u;
}
void test01_01_16() {
	int a = 1;
	float b = 2.5;
	//auto c = add01_02<int, float>(a, b); // error: t,u尚未定义
	auto d = add01_03<int, float>(a, b);
	auto e = add01_04<int, float>(a, b);
	auto f = add01_05<int, float>(a, b);
	std::cout << d << " " << e << " " << f << std::endl;
}
int& foo01_01_17(int& i) {
	return i;
};
float& foo01_01_17(float& f) {
	return f;
};
template <typename T>
auto func01_01_17(T& val)->decltype(foo01_01_17(val)) {
	return foo01_01_17(val);
}
void test01_01_17() {
	int a = 17;
	float b = float(17.1);
	std::cout << func01_01_17<int>(a) << " " << func01_01_17<float>(b) << std::endl;
}

void test01() {
	test01_01_01();
	test01_01_02();
	test01_01_03();
	test01_01_04();
	test01_01_05();
	test01_01_06();
	test01_01_08();
	test01_01_09();
	test01_01_10();
	test01_01_11();
	test01_01_12();
	test01_01_13();
	test01_01_14();
	test01_01_15();
	test01_01_16();
	test01_01_17();
	return;
}
