#include "01-06.h"
#include <iostream>
#include <string>
#include <functional>

// 1.6 lambda表达式
// 1.6.1 lambda表达式的基本用法
// [capture](params) opt->ret{ body; }
// capture是捕获列表，params是参数列表,opt是函数选项(比如:mutable)，ret是函数返回类型,body是函数体。

void test01_06_01() {
	// C++11允许省略lambda表达式的返回值
	auto f1 = [](int a) { return a + 1; };
	std::cout << f1(1) << std::endl;
	
	auto f2 = [](int i) {return i; };
	std::cout << f2(2) << std::endl;
	//// 注意：初始化列表不能用于返回值的自动推导
	//auto f3 = []() {return { 1, 2 }; }; // error:无法推导返回值类型

	// 参数列表可以省略
	auto f4 = []() {return 3; };
	auto f5 = [] {return 4; }; // 省略空参数表
	std::cout << f4() << std::endl;
	std::cout << f5() << std::endl;
}
// lambda表达式的捕获列表
// 1[]不捕获任何变量。
// 2[&]捕获外部作用域中所有变量，并作为引用在函数体中使用(按引用捕获)
// 3[=]捕获外部作用域中的所有变量,并作为副本在函数体中使用(按值捕获)
// 4[=,&foo]按值捕获外部作用域中所有变量，并按引用捕获foo变量
// 5[bar]按值捕获bar变量,同时不捕获其它变量
// 6[this]捕获当前类中this指针，让lambda表达式拥有和当前成员函数同样的访问权限。
// 如果已经使用&或=，就默认添加此项。捕获this的目的是可以在lambda中使用当前类的
// 成员函数和成员变量。
void test01_06_02() {
	class A {
	public:
		int i_ = 0;

		void func(int x, int y) {
			//auto x1 = [] {return i_; };                   // error, 没有捕获外部变量
			auto x2 = [=] {return i_ + x + y; };          // OK,捕获所有外部变量
			auto x3 = [&] {return i_ + x + y; };          // OK,捕获所有外部变量
			auto x4 = [this] {return i_; };               // OK,捕获this指针
			//auto x5 = [this] {return i_ + x + y; };       // error:没有捕获x，y
			auto x6 = [this, x, y] {return i_ + x + y; }; // OK,捕获this指针，x，y
			auto x7 = [this] { return i_++; };            // OK,捕获this指针，并修改成员变量
		}
	};

	int a = 0, b = 1;
	//auto f1 = [] {return a; };              // error:没有捕获外部变量
	auto f2 = [&] {return a++; };           // OK,捕获所有外部变量，并对a执行自加运算
	auto f3 = [=] { return a; };            // OK,捕获所有外部变量，并返回a
	//auto f4 = [=] {return a++; };           // error:a是以复制方式捕获的，无法修改
	//auto f5 = [a] {return a + b; };         // error:没有捕获变量b
	auto f6 = [a, &b] {return a + (++b); }; // OK,捕获a和b的引用，并对b做自加运算
	auto f7 = [=, &b] {return a + (b++); }; // OK,捕获所有变量和b的引用，并对b做自加运算

	// 按值捕获是在闭包定义时把值复制到闭包内的，所以在定义后修改变量值，不会影响闭包已经捕获的结果。
	int c = 2;
	auto f8 = [=] {return c; };
	c = 222;
	std::cout << f8() << std::endl; // 输出为: 2

	// 如果需要修改按值捕获的变量，需要给闭包指定mutable属性，这时修改闭包内的变量，不会影响闭包外的同名变量
	int d = 0;
	//auto f9 = [=] {return d++; }; // error:修改按值捕获的外部变量
	auto f10 = [=]() mutable {return ++d;}; // OK,mutable把闭包属性中的const去掉了
	std::cout << __FUNCTION__ << ": f10() ==" << f10() << std::endl;
	std::cout << __FUNCTION__ << ": d = " << d << std::endl;

	// 使用std::function和std::bind存储lambda表达式
	std::function<int(int)> f11 = [](int a) {return a; };
	std::function<int(void)> f12 = std::bind([](int a) {return a; }, 123);
	std::cout << "f11(11) = " << f11(11) << ", f12() = " << f12() << std::endl;

	// 没有捕获变量的lambda表达式可以转换成一个普通函数指针
	using func_t = int(*)(int);
	func_t f13 = [](int a) {return a; };
	std::cout << "f13(13) = " << f13(13) << std::endl;

	// 捕获变量的lambda表达式不能转换为指针函数
	typedef void(*Ptr)(int*);
	Ptr p1 = [](int* p) {delete p; }; // OK,没捕获变量，可以转换为函数指针
	//Ptr p2 = [&](int* p) {delete p; }; // error:有状态的lambda表达式不能直接转换为指针
}
// 1.6.2 声明式编程风格
#include <vector>
#include <algorithm>
void test01_06_03() {
	// lambda表达式替代函数对象
	class CountEven{
		int& count_;
	public:
		CountEven(int& count) : count_(count) {}
		void operator()(int val) {
			if (!(val & 1)) { // val % 2 == 0
				++count_;
			}
		}
	};
	std::vector<int> v1 = { 1, 2, 3, 4, 5 };
	int even_count1 = 0;
	for_each(v1.begin(), v1.end(), CountEven(even_count1));
	std::cout << "The number of even is " << even_count1 << std::endl;

	// 使用lambda表达式
	std::vector<int> v2 = { 1, 2, 3, 4, 5 };
	int even_count2 = 0;
	for_each(v2.begin(), v2.end(), [&even_count2](int val) {
		if (!(val & 1)) {
			++even_count2;
		}
	});
	std::cout << "The number of even is " << even_count2 << std::endl;
}
// 1.6.3 在需要的时间和地点实现闭包，使程序更灵活
void test01_06_04() {
	// 1.5.3 中查找大于5小于等于10的元素个数
	std::vector<int> v = { 1, 2, 3, 4, 5, 7, 9, 10, 11, 12, 15, 18 };
	auto f = std::bind(std::logical_and<bool>(),
		std::bind(std::greater<int>(), std::placeholders::_1, 5),
		std::bind(std::less_equal<int>(), std::placeholders::_1, 10));
	size_t c3 = std::count_if(v.begin(), v.end(), f);
	std::cout << __FUNCTION__ << ": " << c3 << std::endl;

	// 采用lambda表达式方式
	size_t count = std::count_if(v.begin(), v.end(), [](int x) {
		return x > 5 && x <= 10;
		});
	std::cout << __FUNCTION__ << ": " << count << std::endl;
	// 查找大于10的元素
	size_t c4 = std::count_if(v.begin(), v.end(), [](int x) {
		return x > 10;
		});
	std::cout << __FUNCTION__ << ": " << c4 << std::endl;
	// 查找小于等于10的元素
	size_t c5 = std::count_if(v.begin(), v.end(), [](int x) {
		return x <= 10;
		});
	std::cout << __FUNCTION__ << ": " << c5 << std::endl;
}
void test06() {
	test01_06_01();
	test01_06_02();
	test01_06_03();
	test01_06_04();
	return;
}