#include "05-05.h"

#include <iostream>
#include <thread>
#include <mutex>

// 5.5 call_once/once_flag的使用
// call_once保证在多线程环境下某个函数只调用一次，需要配合once_flag一起使用
std::once_flag flag;

void do_one() {
	std::call_once(flag, []() {std::cout << "Called once" << std::endl; });
}

void test05_05_01() {
	std::thread t1(do_one);
	std::thread t2(do_one);
	std::thread t3(do_one);
	t1.join();
	t2.join();
	t3.join();
}

void test05_05() {
	test05_05_01();
	return;
}