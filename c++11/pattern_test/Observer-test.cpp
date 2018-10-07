#include <Observer.hpp>
#include <iostream>
#include <string>

struct stA {
	int a, b;
	void print(int a, int b) {
		std::cout << a << ", " << b << std::endl;
	}
};

void g_print(int a, int b) {
	std::cout << a << ", " << b << std::endl;
}

void test_events() {
	Events<std::function<void(int, int)>> myevent;
	auto key = myevent.Connect(g_print); // �Ժ�����ʽע��
	stA t;
	auto lambdakey = myevent.Connect([&t](int a, int b) { t.a = a, t.b = b; }); // lambda��ʽע��
	// std::functionע��
	std::function<void(int, int)> f = std::bind(&stA::print, &t, std::placeholders::_1, std::placeholders::_2);
	myevent.Connect(f);
	int a = 1, b = 2;
	myevent.Notify(a, b);  // �㲥���й۲���
	myevent.Disconnect(key);   // �Ƴ��۲���
}