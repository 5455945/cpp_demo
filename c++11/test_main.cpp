#include "test_main.h"
#include <iostream>
#include <string>
#include <list>
using namespace std;

template <typename T, typename U>
auto lfyadd(T t, U u) ->decltype(t + u)
{
	return t + u;
}

template <typename T, typename U>
auto add2(T t, U u) ->decltype(t + u)
{
	return t + u;
}


int main() {
	std::cout << "lfyadd(25, 30.0) = " << lfyadd(25, 30.0) << std::endl;
	std::list<int> l1 = { 0, 1, 4, 3, 5, 7 };
	std::cout << l1.size() << std::endl;
	for (auto it = l1.begin(); it != l1.end();) {
		if (*it == 3) {
			it = l1.erase(it);
		}
		else {
			++it;
		}
	}
	std::cout << "l1:\n";
	for (const auto& it : l1) {
		std::cout << it << ", ";
	}
	std::cout << std::endl;
	std::cout << l1.size() << std::endl;
	
	int a = 0;
	//auto f1 = [=] () { return ++a; }; // error,修改按值捕获的外部变量
	auto f2 = [=] () mutable {return ++a; }; // OK,mutable
	std::cout << "f2() = " << f2() << " a = " << a << std::endl;

	using func_t = int(*)(int);
	func_t f = [](int a) {return a; };
	std::cout << "f(123) = " << f(123) << std::endl;

	test_events();

	test_Singleton();
	TestVisitor();

	TestWrap();

	TestObjPool();

	return 0;
}