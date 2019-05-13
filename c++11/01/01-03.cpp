#include "01-03.h"
#include <iostream>
#include <string>

// 1.3 列表初始化
// 对象初始化
void test01_03_01() {
	int i_arr[3] = { 1, 2, 3 }; // 普通数组
	struct A {
		int x;
		struct B {
			int i;
			int j;
		} b;
	} a = { 1, {2, 3} }; // POD类型，可以使用memcpy的类型
    
	// 拷贝初始化
	int i = 0;
	class Foo {
	public:
		Foo(int) {}
	} foo = 123; // 需要拷贝构造函数

	// 直接初始化
	int j(0);
	Foo bar(123);
}

// 1.3.1 统一的初始化
void test01_03_02() {
	int i_arr[3] = { 1, 2, 3 };
	long l_arr[] = { 1, 3, 4, 5 };
	struct A {
		int x;
		int y;
	} a = { 1, 2 };
	class Foo {
		int a;
	public:
		Foo(int x) : a(x) {};
	private:
		Foo(const Foo&) {};
	};
	Foo a1(123);
	Foo a2 = 123; // C++11 OK的
	//Foo a3 = a2; // 无法访问私有构造函数
	Foo a4 = { 123 };
	Foo a5{ 123 };
	int a6 = { 3 };
	int a7{ 3 };

	int* e1 = new int{ 123 }; // new操作符返回的内存，通过初始化列表在内存初始化时指定初值
	double e2 = double{ 12.12 }; //对匿名对象使用初始化列表，再进行拷贝初始化
	int* e3 = new int[3]{ 1, 2, 3 }; // 堆上动态分配的数组可以使用初始化列表进行初始化
}
// 初始化列表可以用在函数返回值上
struct Foo01_02_03 {
	int a;
	double b;
	Foo01_02_03(int x, double y): a(x), b(y) {};
};
Foo01_02_03 func01_02_03(void) {
	return { 123, 123.1 }; // 列表初始化可以直接使用在函数返回值上。
}
void test01_03_03() {
	Foo01_02_03 a = func01_02_03();
}

// 1.3.2 列表初始化的使用细节
// 对于聚合类型，使用初始化列表相当于对其中每个元素分别赋值；
// 对于非聚合类型，需要先自定义一个构造函数，使用初始化列表将调用它对应的构造函数。
void test01_03_04() {
	struct A {
		int x;
		int y;
	} a = { 1, 2 }; // a.x = 1, a.y = 2;
	struct B {
		int x;
		int y;
		B(int, int) : x(0), y(0) {};// 这个构造函数并没有使用传入参数
	} b = { 1, 2 }; // b.x = 0, b.y = 0;构造函数生效
	std::cout << "test01_03_04: " << a.x << " " << a.y << std::endl;
	std::cout << "test01_03_04: " << b.x << " " << b.y << std::endl;
}
// 聚合类型(Aggregates)的定义
// a类型是一个普通数组(如:int[10],char[],long[2][3])
// b类型是一个类(class,struct,union),且
// b.1 无用户自定义的构造函数
// b.2 无私有(Private)或保护(Protected)的非静态数据成员
// b.3 无基类
// b.4 无虚函数
// b.5 不能有{}和=直接初始化的非静态数据成员。
struct ST2 {
	int x;
	double y;
protected:
	static int z; // 保护型静态成员
};

void test01_03_05() {
	// 数组
	int x[] = { 1, 3, 5 };
	float y[4][3] = {
		{1, 3, 5},
		{2, 4, 6},
		{3, 5, 7}
	};
	char cv[4] = { 'a', 's', 'd', 'f' };
	std::string sa[3] = { "123", "321", "312" };

	// 类
	struct Foo {
		int x;
		double y;
		int z;
		Foo(int, int) {} // 自定义构造函数
	};// 有自定义构造函数，无法将Foo看做一个聚合类型
	//Foo foo{ 1, 2.5, 2 };// error: error C2440: “初始化”: 无法从“initializer list”转换为“test01_03_05::Foo”

	// 有私有(Private)或保护(Protected)的非静态数据成员的情况不能看做聚合类型
	struct ST {
		int x;
		double y;
	protected:
		int z; // 非静态protected类型成员
	}; // 有protected,不是聚合类型
	//ST s{ 1, 2.5, 1 }; // error:error C2440: “初始化”: 无法从“initializer list”转换为“test01_03_05::ST”

	//struct ST21 {
	//	int x;
	//	double y;
	//protected:
	//	static int z; // error C2246: “test01_03_05::ST21::z”: 本地定义的类中的非法静态数据成员
	//};
	ST2 st2{ 1, 2.5 }; // OK,protected是静态类型，没问题

	struct ST3 {
		int x;
		double y;
	private:
		int z;  // 私有非静态成员
	};
	//ST3 st3{ 1, 2.0 }; // error C2440: “初始化”: 无法从“initializer list”转换为“test01_03_05::ST3”

	// 基类和虚函数
	struct ST4 {
		int x;
		int y;
		virtual void F() {} // 虚函数，不能视为聚合类型
	};
	//ST4 s{ 1, 2.5 }; //error:error C2440: “初始化”: 无法从“initializer list”转换为“test01_03_05::ST4”

	struct Base {};
	struct ST5 :public Base { // 派生类
		int x;
		double y;
	};
	//ST5 st5{ 1, 2.5 }; //error C2440: “初始化”: 无法从“initializer list”转换为“test01_03_05::ST5”

	struct ST6 {
		int x;
		double y = 0.0; // 有=
	};
	//ST6 s6{ 1, 2.5 }; // error C2440: “初始化”: 无法从“initializer list”转换为“test01_03_05::ST6”
	struct ST7 {
		int x{ 0 }; // 有{}
		double y;
	};
	//ST7 st7{ 1, 2.5 }; // error C2440: “初始化”: 无法从“initializer list”转换为“test01_03_05::ST7”

	// 对于非聚合类型的情形，想要使用初始化列表，只能自定义一个构造函数。
	struct ST8 {
		int x;
		double y;
		virtual void F() {}
	private:
		int z;
	public:
		ST8(int i, double j, int k) : x(i), y(j), z(k) {}
	};
	ST8 st8{ 1, 2.5, 2 }; // // 构造函数可以使用初始化列表初始化非聚合类型

	// 特殊说明：聚合类型的定义并非递归的。当一个类的非静态成员是非聚合类型型，这个类有可能是聚合类型。
	struct ST9 {
		int x;
		double y;
	private:
		int z;
	}; // 非聚合类型
	//ST9 st9{ 1, 2.5, 3 }; // error:
	struct ST10 {
		ST9 st9;
		int x;
		double y;
	}; // 是聚合类型
	ST10 st10{ {}, 1, 2.5 }; // OK, {}相当于调用ST9的无参构造函数
}

// 1.3.3 初始化列表
// 1 任意长度的初始化列表
#include <map>
#include <string>
#include <set>
#include <vector>
void test01_03_06() {
	int arr1[] = { 1, 2, 3 }; // 数组初始化可以不指定长度，根据初始化列表确定
	std::map<std::string, int> mm = {
		{"1", 1}, {"2", 2}, {"3", 3}
	};
	std::set<int> ss = { 1, 2, 3 };
	std::vector<int> arr2 = { 1, 2, 3, 4, 5 };

	// 
	struct STA {
		int a;
	};
	//STA sta = { 1, 2, 3, 4 }; // error
	STA sta[] = { 1, 2, 3, 4 };
	std::cout << __FUNCTION__ << ":";
	for (auto it : sta) std::cout << it.a << " "; std::cout << std::endl;

	struct STB {
	public:
		STB(std::initializer_list<int>) {};
	};
	STB stb = { 1, 2, 3, 4, 5 }; // OK,只不过类里面没处理初始化列表
}

// 通过std::initializer_list给自定义容器赋值
// std::initializer_list可以做参数
void func01_03_07(std::initializer_list<int> l) {
	std::cout << __FUNCTION__ << ": ";
	for (auto it = l.begin(); it != l.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}
void test01_03_07() {
	class FooVector {
		std::vector<int> content_;
	public:
		FooVector(std::initializer_list<int> list) {
			for (auto it = list.begin(); it != list.end(); ++it) {
				content_.push_back(*it);
			}
		}
	};
	class FooMap {
		std::map<int, int> content_;
		using pair_t = std::map<int, int>::value_type;
	public:
		FooMap(std::initializer_list<pair_t> list) {
			for (auto it = list.begin(); it != list.end(); ++it) {
				content_.insert(*it);
			}
		}
	};
	FooVector fv1 = { 1,2,3,4,5 };
	FooMap fm1 = { {1,2}, {3, 4}, {5, 6} };

	func01_03_07({}); // 一个空集合
	func01_03_07({ 1, 3, 5 }); // 传递{1, 3, 5}
}

// 2 std::initializer_list的一些细节
void test01_03_08() {
	std::initializer_list<int> list = { 1, 2, 3 };
	size_t n = list.size(); // n == 3
	std::cout << __FUNCTION__ << ": n = " << n << std::endl;

	std::initializer_list<int> list1;
	size_t n1 = list1.size(); // n1 == 0
	std::cout << __FUNCTION__ << ": n1 = " << n1 << std::endl;
	list = { 1, 2, 3, 4, 5 };
	n1 = list1.size(); // n1 == 5
	std::cout << __FUNCTION__ << ": n1 = " << n1 << std::endl;
	list = { 3, 1, 2, 4 };
	n1 = list1.size(); // n1 == 4
	std::cout << __FUNCTION__ << ": n1 = " << n1 << std::endl;
}
// std::initializer_list非常高效，其内存仅仅存储了列表中元素的引用，因此不能作为函数的返回值
std::initializer_list<int> func01_03_09() {
	int a = 1, b = 2;
	return { a, b }; // 编程成功，运行错误，函数返回时，a,b的生存期在函数返回已经结束。
}
// 改为如下正常
std::vector<int> func01_03_10() {
	int a = 1, b = 2;
	return { a, b };
}
void test01_03_09() {
	std::initializer_list<int> list = func01_03_09(); // 返回值已经失效
	std::cout << __FUNCTION__ << ": ";
	for (auto it = list.begin(); it != list.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::vector<int> v = func01_03_10();
	for (auto& it : v) {
		std::cout << it << " ";
	}
	std::cout << std::endl;
}

// 1.3.4 防止类型收窄
void test01_03_10() {
	struct Foo {
		Foo(int i) { std::cout << __FUNCTION__ << ": " << i << std::endl; }
	};
	Foo foo(1.2);

	// 列表初始化防止类型收窄
	int a = 1.1;  // OK
	//int b{ 1.1 }; // error:error C2397: 从“double”转换到“int”需要收缩转换

	float fa = 1e40; // OK
	//float fb = { 1e40 }; // error:error C2397: 从“double”转换到“float”需要收缩转换

	float fc = (unsigned long long) - 1; // OK
	//float fd = { (unsigned long long) - 1 }; // error:error C2397: 从“unsigned __int64”转换到“float”需要收缩转换
	float fe = (unsigned long long)1; // OK
	float ff = { (unsigned long long)1 }; // OK

	const int x = 1024, y = 1; // OK
	char c = x; // OK
	//char d = { x }; // error:error C2397: 从“const int”转换到“char”需要收缩转换
	char e = y; // OK
	char f = { y }; // OK
}
void test03() {
	test01_03_01();
	test01_03_02();
	test01_03_03();
	test01_03_04();
	test01_03_05();
	test01_03_06();
	test01_03_07();
	test01_03_08();
	test01_03_09();
	test01_03_10();
	return;
}