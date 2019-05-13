#include "01-05.h"
#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <vector>
// 1.5 std::function��bind����
// 1.5.1 �ɵ��ö���
// �ɵ��ö���(Callable Objets)
// a:��һ������ָ��
// b:��һ������operator()��Ա�����������(�º���)
// c:��һ���ɱ�ת��Ϊ����ָ��Ķ���
// d:��һ�����Ա(����)ָ��
void func01_05_01() {
	std::cout << __FUNCTION__ << std::endl;
}
void test01_05_01() {
	struct Foo {
		void  operator()() { // �º���
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

	void(*func_ptr)(void) = &func01_05_01; // 1.����ָ��
	func_ptr();

	Foo foo; // 2.�º���
	foo();

	Bar bar; // 3.�ɱ�ת��Ϊ����ָ��������
	bar();

	// ==============================================================
	// ******���Ա����ָ������Աָ��û̫�ù�******
	void (A::*mem_func_ptr)(void) = &A::mem_func; // 4.���Ա����ָ��
	int A::*mem_obj_ptr = &A::a_;  // ���������Աָ��
	A aa;
	(aa.*mem_func_ptr)();
	aa.*mem_obj_ptr = 123;
	std::cout << "aa.a_ = " << aa.a_ << std::endl;
	// ==============================================================
}
// 1.5.2 �ɵ��ö����װ��--std::function
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
	std::function<void(void)> fr1 = func01_05_02; // ��һ����ͨ����
	fr1();
	// ��һ����ľ�̬��Ա����
	std::function<int(int)> fr2 = Foo::foo_func;
	std::cout << fr2(123) << std::endl;
	Bar bar;
	fr2 = bar; // ��һ���º���
	std::cout << fr2(345) << std::endl;
}
// std::function��Ϊ�ص�����
void test01_05_03() {
	class A {
		std::function<void()> callback_;
	public:
		A(const std::function<void()>& f) : callback_(f) {}
		void notify() {
			callback_(); // �ص����ϲ�
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
// std::function��Ϊ�������
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

// 1.5.3 std::bind����
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
// std::bind��ռλ��
void output2(int x, int y) {
	std::cout << __FUNCTION__ << ": " << x << " " << y << std::endl;
}
void test01_05_06() {
	std::bind(output2, 1, 2)();  // ��� 1 2
	std::bind(output2, 1, 2)(4, 5, 6);  // ���ڲ������ԣ���� 1 2 
	std::bind(output2, std::placeholders::_1, 2)(1); // ���1 2
	std::bind(output2, 2, std::placeholders::_1)(1); // ���2 1
	//std::bind(output2, 2, std::placeholders::_2)(1); // error:����ʱû�еڶ�������
	std::bind(output2, 2, std::placeholders::_2)(1, 2); // ��� 2 2����һ����������
	std::bind(output2, std::placeholders::_1, std::placeholders::_2)(1, 2); // ��� 1 2
	std::bind(output2, std::placeholders::_2, std::placeholders::_1)(1, 2, 3); // ���2 1����������������
}
// std::bind��std::function���ʹ��
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
	// 1ʹ��bind�򻯺���ǿbind1st��bind2nd
	// ����Ԫ�ش���10��Ԫ�ظ���
	std::vector<int> v = { 1, 2, 3, 4, 5, 7, 9, 10, 11, 12, 15, 18 };
	size_t count1 = std::count_if(v.begin(), v.end(), std::bind1st(std::less<int>(), 10));
	// ����Ԫ��С��10��Ԫ�صĸ���
	size_t count2 = std::count_if(v.begin(), v.end(), std::bind2nd(std::less<int>(), 10));
	std::cout << __FUNCTION__ << ": " << count1 << " " << count2 << std::endl;

	// ʹ��bind
	using std::placeholders::_1;
	size_t c1 = std::count_if(v.begin(), v.end(), std::bind(std::less<int>(), 10, _1));
	size_t c2 = std::count_if(v.begin(), v.end(), std::bind(std::less<int>(), _1, 10));
	std::cout << __FUNCTION__ << ": " << c1 << " " << c2 << std::endl;

	// 2ʹ�����bind����
	//std::bind(std::greater<int>(), std::placeholders::_1, 5); // ����5
	//std::bind(std::less_equal<int>(), std::placeholders::_1, 10); // С�ڵ���10
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