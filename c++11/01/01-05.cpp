#include "01-05.h"
#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
// 1.5 std::function和bind绑定器
// 1.5.1 可调用对象
// 可调用对象(Callable Objets)
// a:是一个函数指针
// b:是一个具有operator()成员函数的类对象(仿函数)
// c:是一个可被转换为函数指针的对象
// d:是一个类成员(函数)指针
void func01_05_01() {
	std::cout << __FUNCTION__ << std::endl;
}
void test01_05_01() {
	struct Foo {
		void  operator()() { // 仿函数
			std::cout << __FUNCTION__ << std::endl;
		}
	};
	struct Bar {
		using fr_t = void(*)(void);
		static void func(void) {
			std::cout << __FUNCTION__ << std::endl;
		}
		operator fr_t(void) {
			return func;
		}
	};
	struct A {
		int a_;
		void mem_func(void) {
			std::cout << __FUNCTION__ << std::endl;
		}
	};

	void(*func_ptr)(void) = &func01_05_01; // 1.函数指针
	func_ptr();

	Foo foo; // 2.仿函数
	foo();

	Bar bar; // 3.可被转换为函数指针的类对象
	bar();

	// ==============================================================
	// ******类成员函数指针和类成员指针没太用过******
	void (A::*mem_func_ptr)(void) = &A::mem_func; // 4.类成员函数指针
	int A::*mem_obj_ptr = &A::a_;  // 或者是类成员指针
	A aa;
	(aa.*mem_func_ptr)();
	aa.*mem_obj_ptr = 123;
	std::cout << "aa.a_ = " << aa.a_ << std::endl;
	// ==============================================================
}
// 1.5.2 可调用对象包装器--std::function
void func01_05_02() {
	std::cout << __FUNCTION__ << std::endl;
}
void test01_05_02() {
	class Foo {
	public:
		static int foo_func(int a) {
			std::cout << __FUNCTION__ << std::endl;
			return a;
		}
	};
	class Bar {
	public:
		int operator()(int a) {
			std::cout << __FUNCTION__ << "(" << a << ") ->: ";
			return a;
		}
	};
	std::function<void(void)> fr1 = func01_05_02; // 绑定一个普通函数
	fr1();
	// 绑定一个类的静态成员函数
	std::function<int(int)> fr2 = Foo::foo_func;
	std::cout << fr2(123) << std::endl;
	Bar bar;
	fr2 = bar; // 绑定一个仿函数
	std::cout << fr2(345) << std::endl;
}
// std::function做为回调函数
void test01_05_03() {
	class A {
		std::function<void()> callback_;
	public:
		A(const std::function<void()>& f) : callback_(f) {}
		void notify() {
			callback_(); // 回调到上层
		}
	};
	class Foo {
	public:
		void operator()(void) {
			std::cout << __FUNCTION__ << std::endl;
		}
	};
	Foo foo;
	A aa(foo);
	aa.notify();
}
// std::function做为函数入参
void call_when_even(int x, const std::function<void(int)>& f) {
	if (!(x & 1)) { // x % 2 == 0
		f(x);
	}
}
void output(int x) { std::cout << x << " "; }
void test01_05_04() {
	for (int i = 0; i < 10; i++) {
		call_when_even(i, output);
	}
	std::cout << std::endl;
}

// 1.5.3 std::bind绑定器
void output_add_2(int x) { std::cout << x + 2 << " "; }
void test01_05_05() {
	{
		std::cout << __FUNCTION__ << ": ";
		auto fr = std::bind(output, std::placeholders::_1);
		for (int i = 0; i < 10; i++) {
			call_when_even(i, fr);
		}
		std::cout << std::endl;
	}
	{
		std::cout << __FUNCTION__ << ": ";
		auto fr = std::bind(output_add_2, std::placeholders::_1);
		for (int i = 0; i < 10; i++) {
			call_when_even(i, fr);
		}
		std::cout << std::endl;
	}
}
// std::bind的占位符
void output2(int x, int y) {
	std::cout << __FUNCTION__ << ": " << x << " " << y << std::endl;
}
void test01_05_06() {
	std::bind(output2, 1, 2)();  // 输出 1 2
	std::bind(output2, 1, 2)(4, 5, 6);  // 多于参数忽略，输出 1 2 
	std::bind(output2, std::placeholders::_1, 2)(1); // 输出1 2
	std::bind(output2, 2, std::placeholders::_1)(1); // 输出2 1
	//std::bind(output2, 2, std::placeholders::_2)(1); // error:调用时没有第二个参数
	std::bind(output2, 2, std::placeholders::_2)(1, 2); // 输出 2 2，第一个参数忽略
	std::bind(output2, std::placeholders::_1, std::placeholders::_2)(1, 2); // 输出 1 2
	std::bind(output2, std::placeholders::_2, std::placeholders::_1)(1, 2, 3); // 输出2 1，第三个参数忽略
}
// std::bind和std::function配合使用
void test01_05_07() {
	class A {
	public:
		int i_ = 0;
		void output(int x, int y) {
			std::cout << __FUNCTION__ << ": " << x << " " << y << std::endl;
		}
	};
	A a;
	std::function<void(int, int)> fr = std::bind(&A::output, &a, std::placeholders::_1, std::placeholders::_2);
	fr(12, 13);
	std::function<int&(void)> fr_i = std::bind(&A::i_, &a);
	fr_i() = 123;
	std::cout << __FUNCTION__ << " a.i_: " << a.i_ << std::endl;
}
void test01_05_08() {
	// 1使用bind简化和增强bind1st和bind2nd
	// 查找元素大于10的元素个数
	std::vector<int> v = { 1, 2, 3, 4, 5, 7, 9, 10, 11, 12, 15, 18 };
	size_t count1 = std::count_if(v.begin(), v.end(), std::bind1st(std::less<int>(), 10));
	// 查找元素小于10的元素的个数
	size_t count2 = std::count_if(v.begin(), v.end(), std::bind2nd(std::less<int>(), 10));
	std::cout << __FUNCTION__ << ": " << count1 << " " << count2 << std::endl;

	// 使用bind
	using std::placeholders::_1;
	size_t c1 = std::count_if(v.begin(), v.end(), std::bind(std::less<int>(), 10, _1));
	size_t c2 = std::count_if(v.begin(), v.end(), std::bind(std::less<int>(), _1, 10));
	std::cout << __FUNCTION__ << ": " << c1 << " " << c2 << std::endl;

	// 2使用组合bind函数
	//std::bind(std::greater<int>(), std::placeholders::_1, 5); // 大于5
	//std::bind(std::less_equal<int>(), std::placeholders::_1, 10); // 小于等于10
	auto f = std::bind(std::logical_and<bool>(),
		std::bind(std::greater<int>(), std::placeholders::_1, 5),
		std::bind(std::less_equal<int>(), std::placeholders::_1, 10));
	size_t c3 = std::count_if(v.begin(), v.end(), f);
	std::cout << __FUNCTION__ << ": " << c3 << std::endl;
}
void test05() {
	test01_05_01();
	test01_05_02();
	test01_05_03();
	test01_05_04();
	test01_05_05();
	test01_05_06();
	test01_05_07();
	test01_05_08();
	return;
}