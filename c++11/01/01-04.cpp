#include "01-04.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
// 1.4 基于范围的for循环
// 1.4.1 for循环的新用法
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

	// 基于范围的for循环
	std::cout << __FUNCTION__ << ": ";
	for (auto n : arr) {
		std::cout << n << " ";
	}
	std::cout << std::endl;

	// 修改值，使用引用
	std::cout << __FUNCTION__ << ": ";
	for (auto& n : arr) {
		std::cout << ++n << " ";
	}
	std::cout << std::endl;
}
// 1.4.2 基于范围的for循环的使用细节
void test01_04_02() {
	std::map<std::string, int> mm = {
		{"1", 1}, {"2", 2}, {"3", 3}
	};
	// 观察基于范围的for循环和普通for循环中迭代变量的不同
	for (auto& val : mm) {
		std::cout << val.first << "->" << val.second << std::endl;
	}
	for (auto ite = mm.begin(); ite != mm.end(); ++ite) {
		std::cout << ite->first << "->" << ite->second << std::endl;
	}
	for (auto& ite = mm.begin(); ite != mm.end(); ++ite) {
		std::cout << ite->first << "->" << ite->second << std::endl;
	}

	// 注意容器本身的一些约束
	std::set<int> ss = { 1, 2, 3 };
	for (auto& val : ss) {
		//std::cout << ++val << std::endl; // ++val error:表达式必须为可修改的左值
	}

	std::map<int, int> m2 = { {1, 1}, {2, 2}, {3, 3} };
	for (auto& val : m2) {
		//// 因为map的限制，val.first是不能修改的
		//std::cout << ++val.first << "->" << ++val.second << std::endl;
	}
}
// 检查基于范围的for的效率
std::vector<int> g_arr = { 1, 2, 3, 4, 5 };
std::vector<int>& get_range(void) {
	std::cout << "get_range ->: " << std::endl;
	return g_arr;
}
void test01_04_03() {
	for (auto& val : get_range()) { // get_range() 只调用一次，高效
		std::cout << val << std::endl;
	}
}

// 迭代中修改容器大小，会失败
void test01_04_04() {
	std::vector<int> arr = { 1, 2, 3, 4, 5 };
	for (auto& val : arr) {
		std::cout << val << std::endl;
		//arr.push_back(0); // 扩大容器，会引发异常
	}

	// 基于范围的for循环，实际上时普通for的语法糖，上面的语句相当于如下：
	auto&& __range = (arr);
	for (auto& __begin = __range.begin(), &__end = __range.end(); __begin != __end; ++__begin) {
		auto val = *__begin;
		std::cout << val << std::endl;
		//arr.push_back(0); // 扩大容器
	}
}

// 1.4.3让基于范围的for循环支持自定义类型
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
	for (auto i : Range(10.5, 15.5))  //[10.5,15.5),步长为1
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(35,27,-1):";
	for (int i : Range(35, 27, -1))  //(27, 35]，步长为-1
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(2,8,0.5):";
	for (auto i : Range(2, 8, 0.5))  //[2,8),步长为0.5
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(8,7,-0.1):";
	for (auto i : Range(8, 7, -0.1))  //(7,8]，步长为-0.1
	{
		cout << " " << i;
	}
	cout << endl;

	cout << "Range('a', 'z'):";
	for (auto i : Range('a', 'z'))  //['a','z'),步长为1
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