#include "01-04.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
// 1.4 ���ڷ�Χ��forѭ��
// 1.4.1 forѭ�������÷�
void do_count(int n) {
	std::cout << n  << " ";
}
void test01_04_01() {
	std::vector<int> arr{ 1, 2, 3, 4, 5 };
	std::cout << __FUNCTION__ << ": ";
	for (auto it = arr.begin(); it != arr.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	// for_each
	std::cout << __FUNCTION__ << ": ";
	std::for_each(arr.begin(), arr.end(), do_count);
	std::cout << std::endl;

	// ���ڷ�Χ��forѭ��
	std::cout << __FUNCTION__ << ": ";
	for (auto n : arr) {
		std::cout << n << " ";
	}
	std::cout << std::endl;

	// �޸�ֵ��ʹ������
	std::cout << __FUNCTION__ << ": ";
	for (auto& n : arr) {
		std::cout << ++n << " ";
	}
	std::cout << std::endl;
}
// 1.4.2 ���ڷ�Χ��forѭ����ʹ��ϸ��
void test01_04_02() {
	std::map<std::string, int> mm = {
		{"1", 1}, {"2", 2}, {"3", 3}
	};
	// �۲���ڷ�Χ��forѭ������ͨforѭ���е��������Ĳ�ͬ
	for (auto& val : mm) {
		std::cout << val.first << "->" << val.second << std::endl;
	}
	for (auto ite = mm.begin(); ite != mm.end(); ++ite) {
		std::cout << ite->first << "->" << ite->second << std::endl;
	}
	for (auto& ite = mm.begin(); ite != mm.end(); ++ite) {
		std::cout << ite->first << "->" << ite->second << std::endl;
	}

	// ע�����������һЩԼ��
	std::set<int> ss = { 1, 2, 3 };
	for (auto& val : ss) {
		//std::cout << ++val << std::endl; // ++val error:���ʽ����Ϊ���޸ĵ���ֵ
	}

	std::map<int, int> m2 = { {1, 1}, {2, 2}, {3, 3} };
	for (auto& val : m2) {
		//// ��Ϊmap�����ƣ�val.first�ǲ����޸ĵ�
		//std::cout << ++val.first << "->" << ++val.second << std::endl;
	}
}
// �����ڷ�Χ��for��Ч��
std::vector<int> g_arr = { 1, 2, 3, 4, 5 };
std::vector<int>& get_range(void) {
	std::cout << "get_range ->: " << std::endl;
	return g_arr;
}
void test01_04_03() {
	for (auto& val : get_range()) { // get_range() ֻ����һ�Σ���Ч
		std::cout << val << std::endl;
	}
}

// �������޸�������С����ʧ��
void test01_04_04() {
	std::vector<int> arr = { 1, 2, 3, 4, 5 };
	for (auto& val : arr) {
		std::cout << val << std::endl;
		//arr.push_back(0); // �����������������쳣
	}

	// ���ڷ�Χ��forѭ����ʵ����ʱ��ͨfor���﷨�ǣ����������൱�����£�
	auto&& __range = (arr);
	for (auto& __begin = __range.begin(), &__end = __range.end(); __begin != __end; ++__begin) {
		auto val = *__begin;
		std::cout << val << std::endl;
		//arr.push_back(0); // ��������
	}
}

// 1.4.3�û��ڷ�Χ��forѭ��֧���Զ�������
#include "range.hpp"
#include <iostream>
using namespace std;
using namespace detail_range;
void TestRange() {
	cout << "Range(15):";
	for (int i : Range(15))  //[0,15)
	{
		cout << " " << i;
	}

	cout << endl;
	cout << "Range(2,6):";
	for (auto i : Range(2, 6))  //[2,6)
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(10.5, 15.5):";
	for (auto i : Range(10.5, 15.5))  //[10.5,15.5),����Ϊ1
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(35,27,-1):";
	for (int i : Range(35, 27, -1))  //(27, 35]������Ϊ-1
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(2,8,0.5):";
	for (auto i : Range(2, 8, 0.5))  //[2,8),����Ϊ0.5
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(8,7,-0.1):";
	for (auto i : Range(8, 7, -0.1))  //(7,8]������Ϊ-0.1
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range('a', 'z'):";
	for (auto i : Range('a', 'z'))  //['a','z'),����Ϊ1
	{
		cout << " " << i;
	}
	cout << endl;
}

void test04() {
	test01_04_01();
	test01_04_02();
	test01_04_03();
	test01_04_04();
	TestRange();
	return;
}