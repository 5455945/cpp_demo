#include "07-01.h"
#include <iostream>
#include <string>

// 7.1 委托构造函数和继承构造函数

// 7.1.1 委托构造函数
// 注1：委托构造函数不能产生环
// 注2：使用委托构造函数就不能再用类成员初始化
class class_c {
public:
	int max;
	int min;
	int middle;

	class_c(int my_max) { max = my_max > 0 ? my_max : 10; }
	// 委托class_c(my_max)构造max，并在构造函数体内定义非构造部分。
	class_c(int my_max, int my_min) :class_c(my_max) { min = my_min > 0 && my_min < max ? my_min : 1; }
	class_c(int my_max, int my_min, int my_middle) : class_c(my_max, my_min) {
		middle = my_middle < max && my_middle > min ? my_middle : 5;
	}
	//// 委托构造函数不能具有其它成员初始化表达式，如下式中的, middle(my_middle)，只能通过成员赋值来初始化
	//class_c(int my_max, int my_min, int my_middle) : class_c(my_max, my_min), middle(my_middle) {}
};
void test07_01_01() {
	class_c c1(1, 3, 2);
}

// 7.1.2 集成构造函数
struct Base07 {
	int x;
	double y;
	std::string s;
	Base07(int i) : x(i), y(0) {}
	Base07(int i, double j) : x(i), y(j) {}
	Base07(int i, double j, const std::string& str) :x(i), y(j), s(str) {}
	void func() { std::cout << "call in Base" << std::endl; }
};
// C++派生类会隐藏基类的同名函数
// 派生类会隐藏基类构造函数
struct Derived07_01 : Base07 {
	void func(int a) { std::cout << "call in Derived " << a << std::endl; }
};
// 可以在派生类中重新定义和基类相同的构造函数
struct Derived07_02 :Base07 {
	Derived07_02(int i) : Base07(i) {}
	Derived07_02(int i, double j) : Base07(i, j) {};
	Derived07_02(int i, double j, const std::string& str) : Base07(i, j, str) {}
	void func(int a) { std::cout << "call in Derived " << a << std::endl; }
};
// 使用继承构造函数特性可以解决派生类隐藏基类同名构造函数问题
struct Derived07_03 : Base07 {
	using Base07::Base07; // 使用基类的构造函数，即继承构造函数
	// 不定义同名函数，基类的func可用
	//void func(int a) { std::cout << "call in Derived " << a << std::endl; }
};
// 在派生类使用基类同名的函数
struct Derived07_04 : Base07 {
	using Base07::Base07; // 使用基类的构造函数，即继承构造函数
	using Base07::func; // 使用基类的同名函数
	void func(int a) { std::cout << "call in Derived " << a << std::endl; }
};
void test07_01_02() {
	//Derived07_01 d(1, 2.5, "ok");  // 编译错误，没有合适的构造函数
	int i = 1;
	double j = 1.23;

	// 派生类定义自己的构造函数
	Derived07_02 d21(i);
	Derived07_02 d22(i, j);
	Derived07_02 d23(i, j, "");
	//d21.func(); // 派生类覆盖基类的同名函数
	d21.func(5);

	// 派生类使用继承构造函数
	Derived07_03 d31(i);
	Derived07_03 d32(i, j);
	Derived07_03 d33(i, j, "");
	d31.func();

	Derived07_04 d41(i);
	Derived07_04 d42(i, j);
	Derived07_04 d43(i, j, "");
	d41.func();
	d41.func(41);
}

// 7.2 原始字面量
// 原始字面量的定义是R"xxx(raw string)xxx)"其中原始字面量必须用()括起来，
// 括号前后可以加其它相同的字符串，所加的字符串会被忽略；所加字符串必须在括号两边同时出现
void test07_02_01() {
	//std::string str1 = R"test(D:\A\B\test.txt)"; // 错误，test没有出现在括号后面
	//std::string str2 = R"test(D:\A\B\test.txt)testaa"; // 错误，括号两边的字符串不匹配
	std::string str3 = R"test(D:\A\B\test.txt)test";
	std::string str4 = R"(D:\A\B\test.txt)";
	std::cout << str3 << std::endl;
	std::cout << str4 << std::endl;
}

// 7.3 final和override关键字
struct A7 {
	// A7::foo is final,限定该虚函数不能被重写
	virtual void foo() final {};
	//// Error: non-virtual function cannot be final,只能修饰虚函数
	//void bar() final {};
};
struct B7 final : A7 {
	//// error: foo cannot be overrideen as it's final in A7
	//void foo() {}
};
//struct C7 : B7 // Error: B7 is final
//{};
struct A7_2 {
	virtual void func() {}
};
struct D : A7_2 {
	// 显示重写
	void func() override {};
};

// 7.4 内存对齐
// 7.4.1 内存对齐
struct MyStruct1 {
	char a;
	int b;
	short c;
	long long d;
	char e;
}; // sizeof(MyStruct1) == 32
struct MyStruct2 {
	char a;
	char e;
	short c;
	int b;
	long long d;
}; // sizeof(MyStruct2) == 16
struct MyStruct3 {
	int b;
	char a;
	short c;
	long long d;
	char e;
};  // sizeof(MyStruct3) == 24
struct MyStruct4 {
	int b;
	char a;
	char f;
	short c;
	long long d;
	char e;
};  // sizeof(MyStruct4) == 24
void test07_04_01() {
	std::cout << sizeof(MyStruct1) << std::endl;
	std::cout << sizeof(MyStruct2) << std::endl;
	std::cout << sizeof(MyStruct3) << std::endl;
	std::cout << sizeof(MyStruct4) << std::endl;
}

// 7.4.2 堆内存的内存对齐
// malloc一般使用当前平台默认的最大最齐数对齐内存；比如：MSVC在32位下一般8字节对齐；在64位下则是16字节对齐
// 当我们需要分配一块具有特定内存对齐的内存块时，在MSVC下应当使用_aligned_malloc,在gcc下一般使用memalign。
// 下面是一个简易aligned_malloc实现
#include <cassert>
inline void* aligned_malloc(size_t size, size_t alignment) {
	// 检查alignment是否是2^N
	assert(!(alignment & (alignment - 1)));
	// 计算出一个最大的offset, sizeof(void*)是为了存储原始指针地址
	size_t offset = sizeof(void*) + (--alignment);

	// 分配一块带offset的内存
	char* p = static_cast<char*>(malloc(offset + size));
	if (!p) return nullptr;

	// 通过“&(~alignment)”把多计算的offset减掉
	void* r = reinterpret_cast<void*>(reinterpret_cast<size_t>(p + offset) & (~alignment));
	// 将r当作一个指向void*的指针，在r当前地址前面放入原始地址
	static_cast<void**>(r)[-1] = p;
	// 返回经过对齐的内存地址
	return r;
}
inline void aligned_free(void *p) {
	// 还原回原始地址，并free
	free(static_cast<void**>(p)[-1]);
}

// 7.4.3 利用alignas指定内存大小
// alignas可以指定内存对齐的大小
alignas(32) long long a = 0;
#define XX 1
struct alignas(XX) MyStruct5 {};
template <size_t YY = 1>
struct alignas(YY) MyStruct6 {};

static const unsigned ZZ = 1;
struct alignas(ZZ) MyStruct7 {};

// alignas只能改大不能该小。如果需要该小，需要用#pragma pack或者C++11中的_Pragma
struct MyStruct8 {
	char a;
	alignas(16) int b;
	short c;
	long long d;
	char e;
};

void test07_04_03() {
	std::cout << sizeof(MyStruct5) << std::endl;
	std::cout << sizeof(MyStruct6<4>) << std::endl;
	std::cout << sizeof(MyStruct7) << std::endl;
	std::cout << sizeof(MyStruct8) << std::endl;
}

// 7.4.4 利用alignof和std::alignment_of获取内存对齐大小
struct MyStruct9 {
	char a;
	int b;
	double c;
};
void test07_04_04() {
	MyStruct9 xx;
	//std::cout << alignof(xx) << std::endl; // error C2061: 语法错误: 标识符“xx”
	std::cout << alignof(MyStruct9) << std::endl;
	std::cout << std::alignment_of<MyStruct9>::value << std::endl;
}

// 7.4.5 内存对齐的类型std::aligned_storage
struct A745 {
	int avg;
	A745(int a, int b) : avg((a + b) / 2) {}
};
void test07_04_05() {
	typedef std::aligned_storage<sizeof(A745), alignof(A745)>::type Aligned_A745;
	Aligned_A745 a, b;
	new (&a) A745(10, 20); // placement new
	b = a;
	std::cout << reinterpret_cast<A745&>(b).avg << std::endl;

	char xx[32];
	::new (xx) MyStruct9; // placement new

	std::aligned_storage<sizeof(MyStruct9), alignof(MyStruct9)>::type yy;
	::new (&yy) MyStruct9;
}

struct alignas(32) MyStruct10 {
	char a;
	int b;
	short c;
	long long d;
	char e;
};
void test07_04_06() {
	void* p = new MyStruct10; // warning C4316: “MyStruct10”: 在堆上分配的对象可能不是对齐 32
}

// 7.4.6 std::max_align_t和std::align操作符
#include <memory>
void test07_04_07() {
	// std::max_align_t用来返回当前平台的最大默认内存对齐类型。
	// 对于malloc返回的内存，其对齐和max_align_t类型的对齐大小应当一致。
	std::cout << alignof(std::max_align_t) << std::endl;
	char buffer[] = "-----------------";
	void* pt = buffer;
	std::size_t space = sizeof(buffer) - 1;
	std::align(alignof(int), sizeof(char), pt, space);
	// 在buffer这个大内存块中，指定内存对齐为alignof(int)，找一块sizeof(char)大小的内存，
	// 并且在找到这块内存后将地址放入pt，将buffer从pt开始的长度放入space。
}

// 7.5 C++11新增的便利算法
// 7.5.1 all_of,any_of和none_of算法
#include <iostream>
#include <algorithm>
#include <vector>
void test07_05_01() {
	std::vector<int> v = { 1, 3, 5, 7, 9 };
	auto isEven = [](int i) { return i % 2 != 0; };
	bool isAllOdd = std::all_of(v.begin(), v.end(), isEven);
	if (isAllOdd) {
		std::cout << "all is odd" << std::endl;
	}
	bool isNoneEven = std::none_of(v.begin(), v.end(), isEven);
	if (isNoneEven) {
		std::cout << "none is even" << std::endl;
	}
	std::vector<int> v1 = { 1, 3, 5, 7, 8, 9 };
	bool anyof = std::any_of(v1.begin(), v1.end(), isEven);
	if (anyof) {
		std::cout << "at least one is even" << std::endl;
	}
}
// 7.5.2 find_if_not
void test07_05_02() {
	std::vector<int> v = { 1, 3, 5, 7, 9, 4 };
	auto isEven = [](int i) {return i % 2 == 0; };
	auto firstEven = std::find_if(v.begin(), v.end(), isEven);
	if (firstEven != v.end()) {
		std::cout << "the first even is " << *firstEven << std::endl;
	}

	// 用find_if查找奇数则需要重新写一个否定含义的判断式
	auto isNotEven = [](int i) {return i % 2 != 0; };
	auto firstOdd = std::find_if(v.begin(), v.end(), isNotEven);
	if (firstOdd != v.end()) {
		std::cout << "the first odd is " << *firstOdd << std::endl;
	}

	// 用find_if_not来查找则无需定义新判断式
	auto odd = std::find_if_not(v.begin(), v.end(), isEven);
	if (odd != v.end()) {
		std::cout << "the first odd is " << *odd << std::endl;
	}
}

// 7.5.3 copy_if
void test07_05_03() {
	std::vector<int> v = { 1, 3, 5, 7, 9, 4 };
	std::vector<int> v1(v.size());
	// 根据条件复制
	auto it = std::copy_if(v.begin(), v.end(), v1.begin(), [](int i) {return i % 2 == 0; });
	// 缩小vector到合适大小
	v1.resize(std::distance(v1.begin(), it));
	for (int& i : v1) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

// 7.5.4 iota
#include <numeric>
#include <array>
void test07_05_04() {
	std::vector<int>v(4);
	// 直接通过iota初始化数组
	std::iota(v.begin(), v.end(), 1);
	for (auto& n : v) {
		std::cout << n << " ";
	}
	std::cout << std::endl;

	std::array<int, 4> a;
	std::iota(a.begin(), a.end(), 1);
	for (auto& n : a) {
		std::cout << n << " ";
	}
	std::cout << std::endl;
}

// 7.5.5 minmax_element
void test07_05_05() {
	std::vector<int> v = { 1, 2, 5, 7, 9, 4 };
	auto result = minmax_element(v.begin(), v.end());
	std::cout << *result.first << " " << *result.second << std::endl;
}

// 7.5.6 is_sorted和is_sorted_until
void test07_05_06() {
	std::vector<int> v = { 1, 2, 5, 7, 9, 4 };
	auto pos = is_sorted_until(v.begin(), v.end());
	for (auto it = v.begin(); it != v.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	bool is_sort = std::is_sorted(v.begin(), v.end());
	std::cout << is_sort << std::endl;
}
void test07() {
	test07_01_01();
	test07_01_02();
	test07_02_01();
	test07_04_01();
	test07_04_03();
	test07_04_04();
	test07_04_05();
	test07_04_06();
	test07_04_07();
	test07_05_01();
	test07_05_02();
	test07_05_03();
	test07_05_04();
	test07_05_05();
	test07_05_06();
	return;
}
