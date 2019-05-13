#include "05-07.h"
#include <iostream>
#include <thread>
#include <future>

// 5.7 线程异步操作函数async
// std::async原型:async(std::launch::async | std::launch::deferred, f, args...)
// 第一个参数为创建线程策略：
// std::launch::async:在调用async时开始创建线程
// std::launch::deferred:调用async时不创建线程，直到future调用了get或者wait时才创建线程
// 第二个参数是线程函数
// 第三个参数是线程函数的参数

void test05_07_01() {
	std::future<int> f1 = std::async(std::launch::async, []() {return 8; });
	std::cout << "test05_07_01: f1.get() = " << f1.get() << std::endl;

	std::future<void> f2 = std::async(std::launch::async, []() {std::cout << 9 << std::endl; });
	f2.wait();

	std::future<int> future = std::async(std::launch::async, []() {
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return 8;
		});
	std::cout << "waiting..." << std::endl;
	std::future_status status;
	do {
		status = future.wait_for(std::chrono::seconds(1));
		if (status == std::future_status::deferred) {
			std::cout << "deferred" << std::endl;
		}
		else if (status == std::future_status::timeout) {
			std::cout << "timeout" << std::endl;
		}
		else if (status == std::future_status::ready) {
			std::cout << "ready!" << std::endl;
		}
	} while (status != std::future_status::ready);
	std::cout << "result is " << future.get() << std::endl;
}

void test05_07() {
	test05_07_01();
	return;
}
