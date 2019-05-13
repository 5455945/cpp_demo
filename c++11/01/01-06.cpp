#include "01-06.h"
#include <iostream>
#include <string>
#include <functional>

// 1.6 lambda���ʽ
// 1.6.1 lambda���ʽ�Ļ����÷�
// [capture](params) opt->ret{ body; }
// capture�ǲ����б�params�ǲ����б�,opt�Ǻ���ѡ��(����:mutable)��ret�Ǻ�����������,body�Ǻ����塣

void test01_06_01() {
	// C++11����ʡ��lambda���ʽ�ķ���ֵ
	auto f1 = [](int a) { return a + 1; };
	std::cout << f1(1) << std::endl;
	
	auto f2 = [](int i) {return i; };
	std::cout << f2(2) << std::endl;
	//// ע�⣺��ʼ���б������ڷ���ֵ���Զ��Ƶ�
	//auto f3 = []() {return { 1, 2 }; }; // error:�޷��Ƶ�����ֵ����

	// �����б����ʡ��
	auto f4 = []() {return 3; };
	auto f5 = [] {return 4; }; // ʡ�Կղ�����
	std::cout << f4() << std::endl;
	std::cout << f5() << std::endl;
}
// lambda���ʽ�Ĳ����б�
// 1[]�������κα�����
// 2[&]�����ⲿ�����������б���������Ϊ�����ں�������ʹ��(�����ò���)
// 3[=]�����ⲿ�������е����б���,����Ϊ�����ں�������ʹ��(��ֵ����)
// 4[=,&foo]��ֵ�����ⲿ�����������б������������ò���foo����
// 5[bar]��ֵ����bar����,ͬʱ��������������
// 6[this]����ǰ����thisָ�룬��lambda���ʽӵ�к͵�ǰ��Ա����ͬ���ķ���Ȩ�ޡ�
// ����Ѿ�ʹ��&��=����Ĭ����Ӵ������this��Ŀ���ǿ�����lambda��ʹ�õ�ǰ���
// ��Ա�����ͳ�Ա������
void test01_06_02() {
	class A {
	public:
		int i_ = 0;

		void func(int x, int y) {
			//auto x1 = [] {return i_; };                   // error, û�в����ⲿ����
			auto x2 = [=] {return i_ + x + y; };          // OK,���������ⲿ����
			auto x3 = [&] {return i_ + x + y; };          // OK,���������ⲿ����
			auto x4 = [this] {return i_; };               // OK,����thisָ��
			//auto x5 = [this] {return i_ + x + y; };       // error:û�в���x��y
			auto x6 = [this, x, y] {return i_ + x + y; }; // OK,����thisָ�룬x��y
			auto x7 = [this] { return i_++; };            // OK,����thisָ�룬���޸ĳ�Ա����
		}
	};

	int a = 0, b = 1;
	//auto f1 = [] {return a; };              // error:û�в����ⲿ����
	auto f2 = [&] {return a++; };           // OK,���������ⲿ����������aִ���Լ�����
	auto f3 = [=] { return a; };            // OK,���������ⲿ������������a
	//auto f4 = [=] {return a++; };           // error:a���Ը��Ʒ�ʽ����ģ��޷��޸�
	//auto f5 = [a] {return a + b; };         // error:û�в������b
	auto f6 = [a, &b] {return a + (++b); }; // OK,����a��b�����ã�����b���Լ�����
	auto f7 = [=, &b] {return a + (b++); }; // OK,�������б�����b�����ã�����b���Լ�����

	// ��ֵ�������ڱհ�����ʱ��ֵ���Ƶ��հ��ڵģ������ڶ�����޸ı���ֵ������Ӱ��հ��Ѿ�����Ľ����
	int c = 2;
	auto f8 = [=] {return c; };
	c = 222;
	std::cout << f8() << std::endl; // ���Ϊ: 2

	// �����Ҫ�޸İ�ֵ����ı�������Ҫ���հ�ָ��mutable���ԣ���ʱ�޸ıհ��ڵı���������Ӱ��հ����ͬ������
	int d = 0;
	//auto f9 = [=] {return d++; }; // error:�޸İ�ֵ������ⲿ����
	auto f10 = [=]() mutable {return ++d;}; // OK,mutable�ѱհ������е�constȥ����
	std::cout << __FUNCTION__ << ": f10() ==" << f10() << std::endl;
	std::cout << __FUNCTION__ << ": d = " << d << std::endl;

	// ʹ��std::function��std::bind�洢lambda���ʽ
	std::function<int(int)> f11 = [](int a) {return a; };
	std::function<int(void)> f12 = std::bind([](int a) {return a; }, 123);
	std::cout << "f11(11) = " << f11(11) << ", f12() = " << f12() << std::endl;

	// û�в��������lambda���ʽ����ת����һ����ͨ����ָ��
	using func_t = int(*)(int);
	func_t f13 = [](int a) {return a; };
	std::cout << "f13(13) = " << f13(13) << std::endl;

	// ���������lambda���ʽ����ת��Ϊָ�뺯��
	typedef void(*Ptr)(int*);
	Ptr p1 = [](int* p) {delete p; }; // OK,û�������������ת��Ϊ����ָ��
	//Ptr p2 = [&](int* p) {delete p; }; // error:��״̬��lambda���ʽ����ֱ��ת��Ϊָ��
}
// 1.6.2 ����ʽ��̷��
#include <vector>
#include <algorithm>
void test01_06_03() {
	// lambda���ʽ�����������
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

	// ʹ��lambda���ʽ
	std::vector<int> v2 = { 1, 2, 3, 4, 5 };
	int even_count2 = 0;
	for_each(v2.begin(), v2.end(), [&even_count2](int val) {
		if (!(val & 1)) {
			++even_count2;
		}
	});
	std::cout << "The number of even is " << even_count2 << std::endl;
}
// 1.6.3 ����Ҫ��ʱ��͵ص�ʵ�ֱհ���ʹ��������
void test01_06_04() {
	// 1.5.3 �в��Ҵ���5С�ڵ���10��Ԫ�ظ���
	std::vector<int> v = { 1, 2, 3, 4, 5, 7, 9, 10, 11, 12, 15, 18 };
	auto f = std::bind(std::logical_and<bool>(),
		std::bind(std::greater<int>(), std::placeholders::_1, 5),
		std::bind(std::less_equal<int>(), std::placeholders::_1, 10));
	size_t c3 = std::count_if(v.begin(), v.end(), f);
	std::cout << __FUNCTION__ << ": " << c3 << std::endl;

	// ����lambda���ʽ��ʽ
	size_t count = std::count_if(v.begin(), v.end(), [](int x) {
		return x > 5 && x <= 10;
		});
	std::cout << __FUNCTION__ << ": " << count << std::endl;
	// ���Ҵ���10��Ԫ��
	size_t c4 = std::count_if(v.begin(), v.end(), [](int x) {
		return x > 10;
		});
	std::cout << __FUNCTION__ << ": " << c4 << std::endl;
	// ����С�ڵ���10��Ԫ��
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