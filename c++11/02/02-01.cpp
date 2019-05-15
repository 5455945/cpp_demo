#include "02-01.h"
#include <iostream>
#include <string>
#include <vector>

// 2.1 右值引用
// 2.1.1 &&的特性
int g_constructCount = 0;
int g_copyConstructCount = 0;
int g_destructCount = 0;
struct A2_1 {
	A2_1() {
		std::cout << "construct: " << ++g_constructCount << std::endl;
	}
	A2_1(const A2_1& a) {
		std::cout << "copy construct: " << ++g_copyConstructCount << std::endl;
	}
	~A2_1() {
		std::cout << "destruct: " << ++g_destructCount << std::endl;
	}
};
A2_1 GetA2_1() {
	return A2_1();
}
// vs2017默认已经开启优化了，构造和析构只调用一次
// construct: 1
// destruct: 1
void test02_01_01() {
	A2_1 a = GetA2_1();
}
void test02_01_02() {
	A2_1&& a2 = GetA2_1();
}

void PrintValue(int& i) {
	std::cout << "lvalue: " << i << std::endl;
}
void PrintValue(int&& i) {
	std::cout << "rvalue: " << i << std::endl;
}
void Forward(int&& i) {
	PrintValue(i);
}
void test02_01_03() {
	int i = 0;
	PrintValue(i); // 左值
	PrintValue(1); // 右值
	// Forward函数接收的是一个右值2，但在转发给PrintValue时又变成左值，因为在
	// Forward中调用PrintValue时，右值i变成命名的对象，编译器会将其当作左值处理
	Forward(2);
}

// 输出引用类型的示例
#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
#include <cxxabi.h>
#endif
#include <memory>
#include <string>
#include <cstdlib>
template <class T>
std::string type_name() {
	typedef typename std::remove_reference<T>::type TR;
	std::unique_ptr<char, void(*)(void*)> own (
#ifndef __GNUC__
		nullptr,
#else
		abi::__cxa_demangle(typeid(TR).name, nullptr, nullptr, nullptr),
#endif
		std::free);
	std::string r = own != nullptr ? own.get() : typeid(TR).name();
	if (std::is_const<TR>::value) {
		r += " const";
	}
	if (std::is_volatile<TR>::value) {
		r += " volatile";
	}
	if (std::is_lvalue_reference<T>::value) {
		r += "&";
	}
	else if (std::is_rvalue_reference<T>::value) {
		r += "&&";
	}
	return r;
}
template<typename T>
void Func(T&& t) {
	std::cout << type_name<T>() << std::endl;
}
void TestReference() {
	std::string str = "test";
	Func(str);
	Func(std::move(str));
}

void test02_01_04() {
	class Foo {};
	std::cout << "test02_01_04: start" << std::endl;
	std::cout << typeid(Foo*[10]).name() << std::endl;
	std::cout << "test02_01_04: ----------------" << std::endl;
	std::cout << typeid(Foo*[10]).raw_name() << std::endl;
	std::cout << "test02_01_04: end" << std::endl;
}

// 2.1.2 右值引用优化性能，避免深拷贝
// A浅拷贝，重复析构
class A2_2 {
public:
	A2_2() :m_ptr(new int(0)) {}
	~A2_2() { delete m_ptr; }
private:
	int* m_ptr;
};
// 为了编码返回值优化，此函数故意这样写
A2_2 GetA22(bool flag) {
	A2_2 a;
	A2_2 b;
	if (flag)
		return a;
	else
		return b;
}
void test02_01_05() {
	// 运行时错误，浅拷贝，重复析构
	//A2_2 a = GetA22(false);
}

// 深拷贝，运行正常
class A2_3 {
public:
	A2_3() : m_ptr(new int(0)) {
		std::cout << "A2_3 construct" << std::endl;
	};
	A2_3(const A2_3& a23) : m_ptr(new int(*a23.m_ptr)) {
		std::cout << "A2_3 copy construct" << std::endl;
	}; // 深拷贝
	~A2_3() {
		std::cout << "A2_3 destruct" << std::endl;
		delete m_ptr;
	}
private:
	int* m_ptr;
};
A2_3 GetA23(bool flag) {
	A2_3 a;
	A2_3 b;
	if (flag)
		return a;
	else
		return b;
}
void test02_01_06() {
	A2_3 a23 = GetA23(false);
}

// 添加移动拷贝构造函数
class A2_4 {
public:
	A2_4() : m_ptr(new int(0)) {
		std::cout << "A2_4 construct" << std::endl;
	};
	A2_4(const A2_4& a24) : m_ptr(new int(*a24.m_ptr)) {
		std::cout << "A2_4 copy construct" << std::endl;
	}; // 深拷贝
	A2_4(A2_4&& a24) : m_ptr(a24.m_ptr) {
		a24.m_ptr = nullptr;
		std::cout << "A2_4 move construct" << std::endl;
	}; // 深拷贝
	~A2_4() {
		std::cout << "A2_4 destruct" << std::endl;
		delete m_ptr;
	}
private:
	int* m_ptr;
};
A2_4 GetA24(bool flag) {
	A2_4 a;
	A2_4 b;
	if (flag)
		return a;
	else
		return b;
}
void test02_01_07() {
	A2_4 a24 = GetA24(false);
}

// 带移动拷贝和赋值的MyString类
class MyString {
private:
	char* m_data;
	size_t m_len;
	void copy_data(const char* s) {
		if (s) {
			m_len = strlen(s);
			m_data = new char[m_len + 1];
			memcpy(m_data, s, m_len);
			m_data[m_len] = '\0';
		}
		else {
			m_data = nullptr;
			m_len = 0;
		}
	}
public:
	MyString() : m_data(nullptr), m_len(0) {
		std::cout << "MyString() constructor" << std::endl;
	}
	MyString(const char* s) {
		if (s) {
			std::cout << "MyString(const char* s) constructor: " << s << std::endl;
			copy_data(s);
		}
		else {
			m_data = nullptr;
			m_len = 0;
		}
	}
	MyString(const MyString& rhs) {
		std::cout << "MyString(const MyString& rhs) copy constructor: " << rhs.m_data << std::endl;
		copy_data(rhs.m_data);
	}
	MyString& operator=(const MyString& rhs) {
		std::cout << "copy assignment constructor: " << (rhs.m_data != nullptr ? rhs.m_data : "") << std::endl;
		if (this != &rhs) {
			delete m_data;
			copy_data(rhs.m_data);
		}
		return *this;
	}
	MyString(MyString&& rhs) {
		std::cout << "Move constructor: " << rhs.m_data << std::endl;
		m_data = rhs.m_data;
		m_len = rhs.m_len;
		rhs.m_data = nullptr;
		rhs.m_len = 0;
	}
	MyString& operator=(MyString&& rhs) {
		std::cout << "Move assignment constructor: " << (rhs.m_data != nullptr ? rhs.m_data : "") << std::endl;
		if (this != &rhs) {
			delete m_data;
			m_data = rhs.m_data;
			m_len = rhs.m_len;
			rhs.m_data = nullptr;
			rhs.m_len = 0;
		}
		return *this;
	}
	~MyString() {
		if (m_data) {
			delete m_data;
			m_data = nullptr;
			m_len = 0;
		}
	}
};
void test02_01_08() {
	MyString a;
	a = MyString("Hello");
	std::vector<MyString> vec;
	vec.push_back(MyString("World"));
	MyString b, c;
	c = b;
	MyString d("");
	b = d;
}

// 2.2 move语义
// 就是使用移动拷贝、移动赋值，避免大的资源拷贝，对原始类型依然会发生拷贝
void test02_02_01() {
	std::string str1("aaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	std::string str2 = std::move(str1); // 移动赋值，避免拷贝
}

// 2.3 forward和完美转发
// 参数转发示例
template<typename T>
void PrintT(T& t) {
	std::cout << "lvalue" << std::endl;
}
template<typename T>
void PrintT(T&& t) {
	std::cout << "rvalue" << std::endl;
}
template<typename T>
void TestForward(T&& v) {
	PrintT(v);
	PrintT(std::forward<T>(v));
	PrintT(std::move(v));
}
void test02_03_01() {
	TestForward(1);
	int x = 1;
	TestForward(x);
	TestForward(std::forward<int>(x));
	/* std::cout
	lvalue
	rvalue
	rvalue
	lvalue
	lvalue
	rvalue
	lvalue
	rvalue
	rvalue
	*/
}

// 万能的函数包装器
template<class Function, class... Args>
inline auto FuncWrapper(Function&& f, Args&& ...args)->decltype(f(std::forward<Args>(args)...)) {
	return f(std::forward<Args>(args)...);
}
// test code
void test0() {
	std::cout << "test0 void" << std::endl;
}
int test1() {
	std::cout << "test1 int" << std::endl;
	return 1;
}
int test2(int x) {
	std::cout << "int test2(int x)" << std::endl;
	return x;
}
std::string test3(std::string s1, std::string s2) {
	std::cout << "std::string test3(std::string s1, std::string s2)" << std::endl;
	return s1 + s2;
}
void test02_03_02() {
	FuncWrapper(test0);
	std::cout << FuncWrapper(test1) << std::endl;
	std::cout << FuncWrapper(test2, 1) << std::endl;
	std::cout << FuncWrapper(test3, "aa", "bb") << std::endl;
}

// 2.4 emplace_back减少内存拷贝和移动
struct A24 {
	int x;
	double y;
	A24(int a, double b) :x(a), y(b) {}
};
void test02_04_01() {
	std::vector<A24> v;
	v.emplace_back(1, 2);
	std::cout << v.size() << std::endl;
}

#include <map>
struct Complicated {
	int year;
	double country;
	std::string name;
	Complicated(int a, double b, std::string c) : year(a), country(b), name(c) {
		std::cout << "is constucted" << std::endl;
	};
	Complicated(const Complicated& other) :year(other.year), country(other.country), name(other.name) {
		std::cout << "is moved" << std::endl;
	}
};
void test02_04_02() {
	std::map<int, Complicated> m;
	int anInt = 4;
	double aDouble = 5.0;
	std::string aString = "C++";
	std::cout << "--insert--" << std::endl;
	m.insert(std::make_pair(4, Complicated(anInt, aDouble, aString)));

	std::cout << "--emplace--" << std::endl;
	m.emplace(4, Complicated(anInt, aDouble, aString));

	std::cout << "--emplace_back--" << std::endl;
	std::vector<Complicated> v;
	v.emplace_back(anInt, aDouble, aString);

	std::cout << "--push_back--" << std::endl;
	v.push_back(Complicated(anInt, aDouble, aString));
	/* std::cout 
	--insert--
	is constucted
	is moved
	is moved
	--emplace--
	is constucted
	is moved
	--emplace_back--
	is constucted
	--push_back--
	is constucted
	is moved
	is moved
	*/
}

// 2.5 unordered container 无序容器
#include <unordered_map>
#include <vector>
#include <bitset>
#include <string>
#include <utility>
struct Key {
	std::string first;
	std::string second;
};
struct KeyHash {
	std::size_t operator()(const Key& k) const {
		return std::hash<std::string>()(k.first) ^ (std::hash<std::string>()(k.second) << 1);
	}
};
struct KeyEqual {
	bool operator()(const Key& lhs, const Key& rhs) const {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}
};
void test02_05_01() {
	// default constructor: empty map
	std::unordered_map<std::string, std::string> m1;

	// list constructor
	std::unordered_map<int, std::string> m2 = {
		{1, "foo"},
		{3, "bar"},
		{2, "baz"},
	};

	// copy constructor
	std::unordered_map<int, std::string> m3 = m2;

	// move constructor
	std::unordered_map<int, std::string> m4 = std::move(m2);

	// range constructor
	std::vector<std::pair<std::bitset<8>, int>> v = { {0x12, 1}, {0x01, -1} };
	std::unordered_map<std::bitset<8>, double> m5(v.begin(), v.end());

	// constructor for a custom type
	std::unordered_map<Key, std::string, KeyHash, KeyEqual> m6 = {
		{ {"John", "Doe"}, "example"},
	{ {"Mary", "Sue"}, "another"}
	};
}

void test02() {
	test02_01_01();
	test02_01_02();
	test02_01_03();
	TestReference();
	test02_01_04();
	test02_01_05();
	test02_01_06();
	test02_01_07();
	test02_01_08();
	test02_02_01();
	test02_03_01();
	test02_03_02();
	test02_04_01();
	test02_04_02();
	test02_05_01();
	return;
}
