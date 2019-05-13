#include "01-07.h"
#include <iostream>
#include <string>
#include <tuple>
#include <functional>
#include <map>

// 1.7 tuple元组
// ================================================
template<class Tuple, std::size_t N>
struct TuplePrinter {
	static void print(const Tuple& t)
	{
		TuplePrinter<Tuple, N - 1>::print(t);
		std::cout << ", " << std::get<N - 1>(t);
	}
};

template<class Tuple>
struct TuplePrinter<Tuple, 1> {
	static void print(const Tuple& t)
	{
		std::cout << std::get<0>(t);
	}
};

template<class... Args>
void print(const std::tuple<Args...>& t)
{
	std::cout << "(";
	TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
	std::cout << ")\n";
}
// ================================================

// tuple元组类似于结构体
void test01_07_01() {
	char* sendPack = nullptr;
	int nSendSize = 0;
	std::tuple<const char*, int> tp1 = std::make_tuple(sendPack, nSendSize);
	//使用std::tie构造
	std::tuple<const char*, int> tp2 = std::tie(sendPack, nSendSize);
	//这个tuple和下面的结构体等价
	struct tp {
		char* p;
		int len;
	};
	{
		// C++14
		std::tuple<int, std::string, float> t1(10, "Test", 3.14);
		std::tuple<int, std::string, float> t2{ 10, "Test", 3.14 };
	}

	//auto pt0 = std::tie(1, "aa", 2); // 错误的赋值方式
	int a = 1;
	std::string b = "aa";
	int c = 2;
	auto tp3 = std::tie(a, b, c);
	std::tuple<int, std::string, int> tp4 = std::tie(a, b, c); // *****
	std::tuple<int&, std::string&, int&> tp44 = std::tie(a, b, c); // *****

	print(tp3);
	print(tp4);
	print(tp44);

	// tuple_cat连接
	std::tuple<int, std::string, float> tp5(10, "Test", 3.14);
	int n = 7;
	auto tp6 = std::tuple_cat(tp5, std::make_pair("Foo", "bar"), tp5, std::tie(n)); // std::tie(n)中的n是引用
	n = 10;
	print(tp6);

	// // 可以使用 std::get<N>(tuple)对tuple中的值做修改
	int x2, y2;
	std::string z2;
	std::tuple<int, std::string, int> tp7(1, "z1", 2);
	x2 = std::get<0>(tp7);
	x2++;
	z2 = std::get<1>(tp7);
	y2 = std::get<2>(tp7);
	std::get<2>(tp7)++;
	print(tp7);
	std::get<1>(tp7) += " exchange";
	print(tp7);

	// tuple读取
	std::string z3;
	int y3;
	std::tie(std::ignore, z3, y3) = tp7;
	std::cout << z3 << " " << y3 << std::endl;

	// 创建右值引用的元组方法: std::forward_as_tuple
	std::map<int, std::string> m;
	m.emplace(std::piecewise_construct,
		std::forward_as_tuple(10),
		std::forward_as_tuple(20, 'a'));
	m.emplace(std::piecewise_construct,
		std::forward_as_tuple(20),
		std::forward_as_tuple(20, 'b'));
	m.emplace(30, "cccccc");
	m.insert(std::pair<int, std::string>(40, "ddddd"));
	for (auto& it : m) {
		std::cout << it.first << "->" << it.second << std::endl;
	}
}
void test07() {
	test01_07_01();
	return;
}