#include "01-01.h"
#include <iostream>
#include <string>

// 1.1 �����Ƶ�
// 1.1.1 auto�����Ƶ�
// auto�ڱ���ʱȷ�����������������
// auto���εı������뱻��ʼ����������ͨ����ʼ����ȷ��auto����������ͣ�������Ҫ���������
// 1 auto�ؼ��ֵ�������
void test01_01_01() {
	auto x = 5;  //OK:x��int����
	auto pi = new auto(1); // OK:pi���Ƶ�Ϊint*
	const auto *v = &x, u = 6; // OK:v��const int*����,u��int����
	static auto y = 0.0;      // OK:y��double����
	//const auto *v2 = &x, u2;  // error:��Ȼv2�Ѿ��Ƶ������ͣ���u2��Ȼ��Ҫд����ĸ�ֵ���֡�
	//auto int r;   // error:auto���ٱ�ʾ�洢����ָʾ��
	//auto s;       // error:auto�޷��Ƶ���s������
	std::cout << typeid(x).name() << " | " << typeid(pi).name() << " | " << typeid(v).name() << " | "
		<< typeid(u).name() << " | " << typeid(y).name() << std::endl;
	// int | int * __ptr64 | int const * __ptr64 | int | double
	
	std::cout << typeid(x).raw_name() << " | " << typeid(pi).raw_name() << " | " << typeid(v).raw_name() << " | "
		<< typeid(u).raw_name() << " | " << typeid(y).raw_name() << std::endl;
}
// 2 auto���Ƶ�����
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

// 3 auto������
//void func01_01_01(auto a = 1) {}  // error:auto�������ں�������
struct Foo {
	//auto var1_ = 0; // error:auto�������ڷǾ�̬��Ա����
	static const auto var2_ = 0; // OK:var2_->static const int
};
template <typename T>
struct Bar {};
void test01_01_03() {
	int arr[10] = { 0 };
	auto aa = arr; // OK: aa->int*
	//auto rr[10] = arr; // error: auto ���Ͳ��ܳ����ڶ���������
	//auto rr[10] = { 0�� 1�� 2�� 3 }; // error: auto �޷���������
	Bar<int> bar;
	//Bar<auto> bb = bar; // error: auto�޷��Ƶ���ģ�����
	(bar);
}
// 4 ʲôʱ��ʹ��auto
#include <map>
// ��1
void test01_01_old1() {
	std::map<double, double> resultMap;
	// ...
	std::map<double, double>::iterator it = resultMap.begin();
	for (; it != resultMap.end(); ++it) {
		// do something
	}
}
// ʹ��auto
void test01_01_04() {
	std::map<double, double> resultMap;
	// ...
	for (auto it = resultMap.begin(); it != resultMap.end(); ++it) {
		// do something
	}
}
// ��2
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

// 1.1.2 decltype�ؼ���
// decltype�����ڱ���ʱ�Ƶ���һ�����ʽ�����͡�decltype���������ʽ��ֵ��
// 1 ��֪���ʽ������
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
// 2 decltype���Ƶ�����decltype(exp)
// �Ƶ�����1��exp�Ǳ�ʶ��������ʱ��ʽ��decltype(exp)��exp������һ��
// �Ƶ�����2��exp�Ǻ������ã�decltype(exp)�ͷ���ֵ������һ��
// �Ƶ�����3�������������exp��һ����ֵ����decltype(exp)��exp���͵���ֵ���ã������exp����һ��
// decltype�����ڱ�ʶ��������ʱ��ʽʾ��
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
	decltype(foo.x) d = 0; // d-> int,����ʱ��ʽ
	(foo);
	std::cout << typeid(a).name() << " | " << typeid(b).name() << " | " << typeid(c).name() << " | " << typeid(d).name() << std::endl;
}
// decltype�����ں������õ�ʾ��
void test01_01_10() {
	const Foo01_09 func_cfoo(void); // ����ֵ
	int& func_int_r(void);   // ��ֵ(lvalue,�ɼ����Ϊ��Ѱֵַ)
	int&& func_int_rr(void); // xֵ(xvalue,��ֵ���ñ�����һ��xvalue)
	int func_int(void);      // ����ֵ(prvalue)
	const int& func_cint_r(void);   // ��ֵ
	const int&& func_cint_rr(void); // xֵ
	const int func_cint(void);      // ����ֵ

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
// �����ŵı��ʽ�ͼӷ�������ʽ
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

// 3 decltypeʵ��Ӧ��
// �������Ͷ�����ܴ��������ʾ��
#include <vector>
template<class ContainerT>
class Foo01_01_12 {
	typename ContainerT::iterator it_; // ���Ͷ������������
public:
	void func(ContainerT& container) {
		it_ = container.begin();
	}
	// ...
};
void test01_01_12() {
	typedef const std::vector<int> container_t;
	container_t arr;
	//Foo01_01_12<container_t> foo; // ��ContainerT��һ��const����ʱ��Ӧ��ʹ��const_iterator��
	//foo.func(arr);
}

// ��const���͵�������ģ���ػ���������
#include <vector>
template<class ContainerT>
class Foo01_01_13 {
	typename ContainerT::iterator it_; // ���Ͷ������������
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
// test01_01_12()/test01_01_13()����ʹ��decltypeд��test01_01_14();vs2017��������
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

//// ��׼���е�nullptr_t��size_t�����Ͷ���
//typedef decltype(nullptr) nullptr_t;
//typedef decltype(sizeof(0)) size_t;

// 1.1.3 �������ͺ����﷨--auto��decltype���ʹ��
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
decltype(t + u) add01_02(T t, U u) { // error: t,u ��δ����
	return t + u;
}
template <typename T, typename U>
decltype(T() + U()) add01_03(T t, U u) {
	return t + u;
}
template <typename T, typename U>
decltype((*(T*)0) + (*(U*)0)) add01_04(T t, U u) { // C++03/98������
	return t + u;
}
// ��ȷ��C++11�������ͺ����﷨
template <typename T, typename U>
auto add01_05(T t, U u)->decltype(t + u) {
	return t + u;
}
void test01_01_16() {
	int a = 1;
	float b = 2.5;
	//auto c = add01_02<int, float>(a, b); // error: t,u��δ����
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
