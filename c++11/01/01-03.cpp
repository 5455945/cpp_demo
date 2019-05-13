#include "01-03.h"
#include <iostream>
#include <string>

// 1.3 �б��ʼ��
// �����ʼ��
void test01_03_01() {
	int i_arr[3] = { 1, 2, 3 }; // ��ͨ����
	struct A {
		int x;
		struct B {
			int i;
			int j;
		} b;
	} a = { 1, {2, 3} }; // POD���ͣ�����ʹ��memcpy������
    
	// ������ʼ��
	int i = 0;
	class Foo {
	public:
		Foo(int) {}
	} foo = 123; // ��Ҫ�������캯��

	// ֱ�ӳ�ʼ��
	int j(0);
	Foo bar(123);
}

// 1.3.1 ͳһ�ĳ�ʼ��
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
	Foo a2 = 123; // C++11 OK��
	//Foo a3 = a2; // �޷�����˽�й��캯��
	Foo a4 = { 123 };
	Foo a5{ 123 };
	int a6 = { 3 };
	int a7{ 3 };

	int* e1 = new int{ 123 }; // new���������ص��ڴ棬ͨ����ʼ���б����ڴ��ʼ��ʱָ����ֵ
	double e2 = double{ 12.12 }; //����������ʹ�ó�ʼ���б��ٽ��п�����ʼ��
	int* e3 = new int[3]{ 1, 2, 3 }; // ���϶�̬������������ʹ�ó�ʼ���б���г�ʼ��
}
// ��ʼ���б�������ں�������ֵ��
struct Foo01_02_03 {
	int a;
	double b;
	Foo01_02_03(int x, double y): a(x), b(y) {};
};
Foo01_02_03 func01_02_03(void) {
	return { 123, 123.1 }; // �б��ʼ������ֱ��ʹ���ں�������ֵ�ϡ�
}
void test01_03_03() {
	Foo01_02_03 a = func01_02_03();
}

// 1.3.2 �б��ʼ����ʹ��ϸ��
// ���ھۺ����ͣ�ʹ�ó�ʼ���б��൱�ڶ�����ÿ��Ԫ�طֱ�ֵ��
// ���ڷǾۺ����ͣ���Ҫ���Զ���һ�����캯����ʹ�ó�ʼ���б���������Ӧ�Ĺ��캯����
void test01_03_04() {
	struct A {
		int x;
		int y;
	} a = { 1, 2 }; // a.x = 1, a.y = 2;
	struct B {
		int x;
		int y;
		B(int, int) : x(0), y(0) {};// ������캯����û��ʹ�ô������
	} b = { 1, 2 }; // b.x = 0, b.y = 0;���캯����Ч
	std::cout << "test01_03_04: " << a.x << " " << a.y << std::endl;
	std::cout << "test01_03_04: " << b.x << " " << b.y << std::endl;
}
// �ۺ�����(Aggregates)�Ķ���
// a������һ����ͨ����(��:int[10],char[],long[2][3])
// b������һ����(class,struct,union),��
// b.1 ���û��Զ���Ĺ��캯��
// b.2 ��˽��(Private)�򱣻�(Protected)�ķǾ�̬���ݳ�Ա
// b.3 �޻���
// b.4 ���麯��
// b.5 ������{}��=ֱ�ӳ�ʼ���ķǾ�̬���ݳ�Ա��
struct ST2 {
	int x;
	double y;
protected:
	static int z; // �����;�̬��Ա
};

void test01_03_05() {
	// ����
	int x[] = { 1, 3, 5 };
	float y[4][3] = {
		{1, 3, 5},
		{2, 4, 6},
		{3, 5, 7}
	};
	char cv[4] = { 'a', 's', 'd', 'f' };
	std::string sa[3] = { "123", "321", "312" };

	// ��
	struct Foo {
		int x;
		double y;
		int z;
		Foo(int, int) {} // �Զ��幹�캯��
	};// ���Զ��幹�캯�����޷���Foo����һ���ۺ�����
	//Foo foo{ 1, 2.5, 2 };// error: error C2440: ����ʼ����: �޷��ӡ�initializer list��ת��Ϊ��test01_03_05::Foo��

	// ��˽��(Private)�򱣻�(Protected)�ķǾ�̬���ݳ�Ա��������ܿ����ۺ�����
	struct ST {
		int x;
		double y;
	protected:
		int z; // �Ǿ�̬protected���ͳ�Ա
	}; // ��protected,���Ǿۺ�����
	//ST s{ 1, 2.5, 1 }; // error:error C2440: ����ʼ����: �޷��ӡ�initializer list��ת��Ϊ��test01_03_05::ST��

	//struct ST21 {
	//	int x;
	//	double y;
	//protected:
	//	static int z; // error C2246: ��test01_03_05::ST21::z��: ���ض�������еķǷ���̬���ݳ�Ա
	//};
	ST2 st2{ 1, 2.5 }; // OK,protected�Ǿ�̬���ͣ�û����

	struct ST3 {
		int x;
		double y;
	private:
		int z;  // ˽�зǾ�̬��Ա
	};
	//ST3 st3{ 1, 2.0 }; // error C2440: ����ʼ����: �޷��ӡ�initializer list��ת��Ϊ��test01_03_05::ST3��

	// ������麯��
	struct ST4 {
		int x;
		int y;
		virtual void F() {} // �麯����������Ϊ�ۺ�����
	};
	//ST4 s{ 1, 2.5 }; //error:error C2440: ����ʼ����: �޷��ӡ�initializer list��ת��Ϊ��test01_03_05::ST4��

	struct Base {};
	struct ST5 :public Base { // ������
		int x;
		double y;
	};
	//ST5 st5{ 1, 2.5 }; //error C2440: ����ʼ����: �޷��ӡ�initializer list��ת��Ϊ��test01_03_05::ST5��

	struct ST6 {
		int x;
		double y = 0.0; // ��=
	};
	//ST6 s6{ 1, 2.5 }; // error C2440: ����ʼ����: �޷��ӡ�initializer list��ת��Ϊ��test01_03_05::ST6��
	struct ST7 {
		int x{ 0 }; // ��{}
		double y;
	};
	//ST7 st7{ 1, 2.5 }; // error C2440: ����ʼ����: �޷��ӡ�initializer list��ת��Ϊ��test01_03_05::ST7��

	// ���ڷǾۺ����͵����Σ���Ҫʹ�ó�ʼ���б�ֻ���Զ���һ�����캯����
	struct ST8 {
		int x;
		double y;
		virtual void F() {}
	private:
		int z;
	public:
		ST8(int i, double j, int k) : x(i), y(j), z(k) {}
	};
	ST8 st8{ 1, 2.5, 2 }; // // ���캯������ʹ�ó�ʼ���б��ʼ���Ǿۺ�����

	// ����˵�����ۺ����͵Ķ��岢�ǵݹ�ġ���һ����ķǾ�̬��Ա�ǷǾۺ������ͣ�������п����Ǿۺ����͡�
	struct ST9 {
		int x;
		double y;
	private:
		int z;
	}; // �Ǿۺ�����
	//ST9 st9{ 1, 2.5, 3 }; // error:
	struct ST10 {
		ST9 st9;
		int x;
		double y;
	}; // �Ǿۺ�����
	ST10 st10{ {}, 1, 2.5 }; // OK, {}�൱�ڵ���ST9���޲ι��캯��
}

// 1.3.3 ��ʼ���б�
// 1 ���ⳤ�ȵĳ�ʼ���б�
#include <map>
#include <string>
#include <set>
#include <vector>
void test01_03_06() {
	int arr1[] = { 1, 2, 3 }; // �����ʼ�����Բ�ָ�����ȣ����ݳ�ʼ���б�ȷ��
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
	STB stb = { 1, 2, 3, 4, 5 }; // OK,ֻ����������û�����ʼ���б�
}

// ͨ��std::initializer_list���Զ���������ֵ
// std::initializer_list����������
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

	func01_03_07({}); // һ���ռ���
	func01_03_07({ 1, 3, 5 }); // ����{1, 3, 5}
}

// 2 std::initializer_list��һЩϸ��
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
// std::initializer_list�ǳ���Ч�����ڴ�����洢���б���Ԫ�ص����ã���˲�����Ϊ�����ķ���ֵ
std::initializer_list<int> func01_03_09() {
	int a = 1, b = 2;
	return { a, b }; // ��̳ɹ������д��󣬺�������ʱ��a,b���������ں��������Ѿ�������
}
// ��Ϊ��������
std::vector<int> func01_03_10() {
	int a = 1, b = 2;
	return { a, b };
}
void test01_03_09() {
	std::initializer_list<int> list = func01_03_09(); // ����ֵ�Ѿ�ʧЧ
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

// 1.3.4 ��ֹ������խ
void test01_03_10() {
	struct Foo {
		Foo(int i) { std::cout << __FUNCTION__ << ": " << i << std::endl; }
	};
	Foo foo(1.2);

	// �б��ʼ����ֹ������խ
	int a = 1.1;  // OK
	//int b{ 1.1 }; // error:error C2397: �ӡ�double��ת������int����Ҫ����ת��

	float fa = 1e40; // OK
	//float fb = { 1e40 }; // error:error C2397: �ӡ�double��ת������float����Ҫ����ת��

	float fc = (unsigned long long) - 1; // OK
	//float fd = { (unsigned long long) - 1 }; // error:error C2397: �ӡ�unsigned __int64��ת������float����Ҫ����ת��
	float fe = (unsigned long long)1; // OK
	float ff = { (unsigned long long)1 }; // OK

	const int x = 1024, y = 1; // OK
	char c = x; // OK
	//char d = { x }; // error:error C2397: �ӡ�const int��ת������char����Ҫ����ת��
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