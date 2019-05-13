#include "01-02.h"
#include <map>
#include <iostream>
#include <string>

// 1.2 ģ���ϸ�ڸĽ�
// 1.2.1 ģ����Ҽ�����
// ��C++98/03�У�ģ�������Ҽ����Żᱨ��
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
	Foo01_02_01<A01_02_01<int>>::type xx1; // ��C++98/03��׼�б������C++11������

	//// ��C++11������error C2143: �﷨����: ȱ�١�;��(�ڡ�>����ǰ��)��error C2059: �﷨����:��>��
	//Foo01_02_02 < 100 >> 2 > xx2;

	// ʹ��������ȷ����
	Foo01_02_02 < (100 >> 2) > xx3;
	(xx1); // ��������C4101,warning C4101: ��xx1��: δ���õľֲ�����
	(xx3); // ��������C4101
}

// 1.2.2ģ�����
typedef unsigned int uint_t;
void func01_02_01(unsigned int) {};
// void func01_02_02(uint_t) {}; // error C2084: ������void func(unsigned int)����������

// ��ΰ�������������������һ�����ʹ��棿
typedef std::map<std::string, int> map_int_t;
typedef std::map<std::string, std::string>map_str_t;
// C++98/03��׼
template <typename Val>
struct str_map { // �������
	typedef std::map<std::string, Val > type;
	// ...
};
str_map<int>::type map1;
str_map<std::string>::type map2;
// C++11��׼��ģ�����
template <typename Val>
using str_map_t = std::map<std::string, Val>;
str_map_t<int> map3;
str_map_t<std::string> map4;

// �ض��� unsinged int
typedef unsigned int uint_t;
using uint_t = unsigned int;
// �ض���std::map
typedef std::map<std::string, int> map_int_t;
using map_int_t = std::map<std::string, int>;

// ��������
typedef void(*func_t01)(int, int);
using func_t02 = void(*)(int, int);

// C++98/03
template <typename T>
struct func_t03 {
	typedef void(*type)(T, T);
};
// ʹ��func_tģ��
func_t03<int>::type funct03_xx1;

// C++11
template <typename T>
using func_t04 = void(*)(T, T);
// ʹ�ú���ģ��
func_t04<int> funct04_xx2;

// 1.2.3 ����ģ���Ĭ��ģ�����
template <typename T, typename U = int, U N = 0>
struct Foo01_02_04 {
	T a;
	U b;
};
template <typename T = int> // C++98/03�в�����C++11����
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
// Ĭ�ϲ���,Ĭ�ϲ������ͣ������Զ��Ƶ����е㸴��
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