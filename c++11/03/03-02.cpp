#include "03-02.h"
#include <iostream>
#include <tuple>
#include <string>

// 3.2 �ɱ����ģ��
// 3.2.1 �ɱ����ģ�庯��
template <class... T>
void func03_02_01(T... args) {
	std::cout << sizeof...(args) << std::endl; // ��ӡ��θ���
}
void test03_02_01() {
	std::cout << __FUNCTION__ << " start" << std::endl;
	func03_02_01();
	func03_02_01(1, 2);
	func03_02_01(1, 2.5, "test");
	std::cout << __FUNCTION__ << " end" << std::endl;
}
// 1�ݹ麯����ʽչ��������
// ��ֹ����
void func03_02_02_print() {
	std::cout << "empty" << std::endl;
}
// չ������
template<class T, class ...Args>
void func03_02_02_print(T head, Args... rest) {
	std::cout << "parameters " << head << std::endl;
	func03_02_02_print(rest...);
}
void test03_02_02() {
	std::cout << __FUNCTION__ << " start" << std::endl;
	func03_02_02_print(1, 2, 3, 4);
	std::cout << __FUNCTION__ << " end" << std::endl;
}
//// �ݹ���ֹ����Ҳ����д��,�������������
//template<typename T, typename T1>
//void func03_02_02_print(T t, T1 t1) {
//	std::cout << t << " " << t1 << std::endl;
//}

// ʹ��type_traitsչ��������
template<std::size_t I = 0, typename Tuple>
typename std::enable_if<I == std::tuple_size<Tuple>::value>::type func03_02_03_printp(Tuple t) { }
template<std::size_t I = 0, typename Tuple>
typename std::enable_if < I <std::tuple_size<Tuple>::value>::type func03_02_03_printp(Tuple t) {
	std::cout << std::get<I>(t) << std::endl;
	func03_02_03_printp<I + 1>(t);
}
template<typename ...Args>
void func03_02_03_print(Args... args) {
	func03_02_03_printp(std::make_tuple(args...));
}
void test03_02_03() {
	std::cout << __FUNCTION__ << " start" << std::endl;
	func03_02_03_print();
	func03_02_03_print(1);
	func03_02_03_print(1, 2, 3, 4, 5);
	std::cout << __FUNCTION__ << " end" << std::endl;
}
// ʹ�ö��ű��ʽ�ͳ�ʼ���б�չ������ 1
template<class T>
void func03_02_04_printarg(T t) {
	std::cout << t << std::endl;
}
template<class ...Args>
void func03_02_04_expand(Args... args) {
	int arr[] = { (func03_02_04_printarg(args), 0)... };
}
void test03_02_04() {
	std::cout << __FUNCTION__ << " start" << std::endl;
	//func03_02_04_expand(); // error C2466: ���ܷ��䳣����СΪ 0 ������
	func03_02_04_expand(1);
	func03_02_04_expand(1, 2, 3, 4, 5);
	std::cout << __FUNCTION__ << " end" << std::endl;
}
// ʹ�ö��ű��ʽ�ͳ�ʼ���б�չ������ 2��ʹ��std::initializer_list
template<class T>
void func03_02_05_printarg(T t) {
	std::cout << t << std::endl;
}
template<class ...Args>
void func03_02_05_expand(Args... args) {
	std::initializer_list<int>{(func03_02_05_printarg(args), 0)... };
}
void test03_02_05() {
	std::cout << __FUNCTION__ << " start" << std::endl;
	func03_02_05_expand();
	func03_02_05_expand(1);
	func03_02_05_expand(1, 2, 3, 4, 5);
	std::cout << __FUNCTION__ << " end" << std::endl;
}
// ʹ�ö��ű��ʽ�ͳ�ʼ���б�չ������ 3,ʹ��lambda���ʽ
template<class ...Args>
void func03_02_06_expand(Args... args) {
	// ��vs2015�£�û����������lambda���ʽû�б�����
	std::initializer_list<int>{([&] {std::cout << args << std::endl; }, 0)... };
}
void test03_02_06() {
	std::cout << __FUNCTION__ << " start" << std::endl;
	func03_02_06_expand();
	func03_02_06_expand(1);
	func03_02_06_expand(1, 2, 3, 4, 5);
	std::cout << __FUNCTION__ << " end" << std::endl;
}
// 3.2.2 �ɱ����ģ����
//// tuple����һ���ɱ����ģ����
//template <class... Types> class tuple;
// �ɱ����ģ�������Я������������������Ĳ���
std::tuple<int> tp1 = std::make_tuple(1);
std::tuple<int, double> tp2 = std::make_tuple(1, 2.5);
std::tuple<int, double, std::string> tp3 = std::make_tuple(1, 2.5, "");
// �ɱ����ģ��Ҳ���Դ�0������
std::tuple<> tp;
// 1.ģ��ݹ���ػ���ʽչ��������(�ݹ�+�ػ�)

// A.����ʽ����
// ��һ���֣�ǰ������������Sum1��һ���ɱ����ģ��
template<typename... Args> struct Sum1;
// �ڶ����֣�չ���Ŀɱ����ģ���࣬���߱�������εݹ�չ��������
template<typename First, typename... Rest>
struct Sum1<First, Rest...> {
	enum { value = Sum1<First>::value + Sum1<Rest...>::value };
};
// �������֣��ػ�������ֹ�ݹ�
template<typename Last> // չ�������һ��������ֹ
struct Sum1<Last> {
	enum { value = sizeof(Last) };
};
//// �ݹ���ֹ���������ж���д��
//// չ�������������ֹ,
//template<> struct Sum1<> { enum { value = 0 }; };
void test03_02_07() {
	std::cout << Sum1<int, double, short>::value << std::endl;
}

// B.����ʽ����
template<typename First, typename ...Rest>
struct Sum2 {
	enum { value = Sum2<First>::value + Sum2<Rest...>::value };
};
template<typename Last>
struct Sum2<Last> {
	enum { value = sizeof(Last) };
};
//// չ�������������ֹ,����ʽ��ʽ���ܵ����������ֹ
//template<> struct Sum2<> { enum { value = 0 }; };
void test03_02_08() {
	std::cout << Sum2<int, double, short>::value << std::endl;
}

// ʹ��std::integral_constant������ö�ٶ���value
// ǰ������
template<typename ...Args> struct Sum3;
// ��������
template<typename First, typename... Rest>
struct Sum3<First, Rest...> : std::integral_constant<int, Sum3<First>::value + Sum3<Rest...>::value> {};
// �ݹ���ֹ
template<typename Last>
struct Sum3<Last> : std::integral_constant<int, sizeof(Last)> {};
void test03_02_09() {
	std::cout << Sum3<int, double, short>::value << std::endl;
}

// 2 �̳з�ʽչ��������(�̳�+�ػ�)
// �������еĶ���
template<int...> struct IndexSeq1 {};
// �̳з�ʽ����ʼչ��������
template<int N, int... Indexes1>
struct MakeIndexes1 : MakeIndexes1<N - 1, N - 1, Indexes1...> {};
// ģ���ػ�����ֹչ��������������
template<int... Indexes1>
struct MakeIndexes1<0, Indexes1...> {
	typedef IndexSeq1<Indexes1...> type;
};
void test03_02_10() {
	using T = MakeIndexes1<3>::type;
	std::cout << typeid(T).name() << std::endl;
	// struct IndexSeq1<0,1,2>
}
// ����ʽ
// �������еĶ���
template<int...> struct IndexSeq2 {};
// �̳з�ʽ����ʼչ��������
template<int N, int... Indexes2>
struct MakeIndexes2 : MakeIndexes2<N - 1, Indexes2..., N - 1> {}; // ��1�Ƚϣ���������˳��
// ģ���ػ�����ֹչ��������������
template<int... Indexes2>
struct MakeIndexes2<0, Indexes2...> {
	typedef IndexSeq2<Indexes2...> type;
};
void test03_02_11() {
	using T = MakeIndexes2<3>::type;
	std::cout << typeid(T).name() << std::endl;
	// struct IndexSeq2<2,1,0>
}
// ��IndexSeqչ������ӡ�ɱ����˳��
template<int...> struct IndexSeq3 {};
template<int N, int... Indexes3>
struct MakeIndexes3 {
	// using type = MakeIndexes3<N - 1, N - 1, Indexes3...>::type;
	using type = typename MakeIndexes3<N - 1, N - 1, Indexes3...>::type;
};
template<int... Indexes3>
struct MakeIndexes3<0, Indexes3...> {
	using type = IndexSeq3<Indexes3...>;
};
template<int ...Indexes3, typename ...Args>
void print_helper3(IndexSeq3<Indexes3...>, std::tuple<Args...>&& tup) {
	print3(std::get<Indexes3>(tup)...); // ��tupleת��Ϊ�����������ڵ��÷���1
}
template<typename ...Args>
void print3(Args... args) {
	print_helper3(typename MakeIndexes3<sizeof...(Args)>::type(), std::make_tuple(args...));
}
void test03_02_12() {
}

// 3.2.3 �ɱ����ģ�������ظ�����
// A.C++98/03ʵ�ֵĴ�ӡ����
template <typename T>
void Print030213(T t) {
	std::cout << t << std::endl;
}
template <typename T1, typename T2>
void Print030213(T1 t1, T2 t2) {
	std::cout << t1 << " " << t2 << std::endl;
}
template <typename T1, typename T2, typename T3>
void Print030213(T1 t1, T2 t2, T3 t3) {
	std::cout << t1 << " " << t2 << " " << t3 << std::endl;
}
template <typename T1, typename T2, typename T3, typename T4>
void Print030213(T1 t1, T2 t2, T3 t3, T4 t4) {
	std::cout << t1 << " " << t2 << " " << t3 << " " << t4 << std::endl;
}
template <typename T1, typename T2, typename T3, typename T4, typename T5>
void Print030213(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5) {
	std::cout << t1 << " " << t2 << " " << t3 << " " << t4 << " " << t5 << std::endl;
}
// ʹ��C++11�Ŀɱ����ģ�庯��
void Print030213B() { // ��ֹ������֧��0������
}
template <typename T, typename ...Args>
void Print030213B(T t, Args ...args) {
	std::cout << t << " ";
	Print030213B(args...);
}
void test03_02_13() {
	//Print030213();
	Print030213(1, 2.5, "test13");
	Print030213B();
	Print030213B(1, 2.4, "test13B");
}
// ��������ĳ��󹤳̺���
// C++98/03�ķ���
template <typename T>
T* Instance() {
	return new T();
}
template <typename T, typename T0>
T* Instance(T0 args0) {
	return new T(args0);
}
template <typename T, typename T0, typename T1>
T* Instance(T0 args0, T1 args1) {
	return new T(args0, args1);
}
template <typename T, typename T0, typename T1, typename T2>
T* Instance(T0 args0, T1 args1, T2 args2) {
	return new T(args0, args1, args2);
}
template <typename T, typename T0, typename T1, typename T2, typename T3>
T* Instance(T0 args0, T1 args1, T2 args2, T3 args3) {
	return new T(args0, args1, args2, args3);
}
template <typename T, typename T0, typename T1, typename T2, typename T3, typename T4>
T* Instance(T0 args0, T1 args1, T2 args2, T3 args3, T4 args4) {
	return new T(args0, args1, args2, args3, args4);
}
// C++11��д��
//template <typename T, typename ... Args>
//T * InstanceC11(Args... args) {  // ֵ�������������ظ����
//	return new T(args...);
//};
template<typename T, typename... Args>
T* InstanceC11(Args&&... args) {
	return new T(std::forward<Args>(args)...); // ʹ������ת����ʽ
};
//template<typename T, typename... Args>
//T* Instance(Args&&... args) {
//	return new T(std::forward<Args>(args)...);
//}
void test03_02_14() {
	struct A { A(int) {} };
	struct B { B(int, int) {} };
	A* pa = Instance<A>(1);
	B* pb = Instance<B>(1, 2);
	A* pa11 = InstanceC11<A>(1);
	B* pb11 = InstanceC11<B>(1, 2);
	delete pa;
	delete pb;
	delete pa11;
	delete pb11;
}
void test03_02() {
	test03_02_01();
	test03_02_02();
	test03_02_03();
	test03_02_04();
	test03_02_05();
	test03_02_06();
	test03_02_07();
	test03_02_08();
	test03_02_09();
	test03_02_10();
	test03_02_11();
	test03_02_12();
	test03_02_13();
	test03_02_14();
	return;
}