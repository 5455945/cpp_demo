#include "03-02.h"
#include <iostream>
#include <tuple>

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
void test03_02() {
	test03_02_01();
	test03_02_02();
	test03_02_03();
	test03_02_04();
	test03_02_05();
	test03_02_06();
	return;
}