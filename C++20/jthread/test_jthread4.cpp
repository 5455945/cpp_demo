// C ++ 20中的新线程（jthread）功能
// https://www.jianshu.com/p/c610ad5db6b7
#include "jthread.hpp"
#include <chrono>
#include <iostream>

void sleep(const int seconds) {
	std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void test_thread01() {
	std::thread t{ [] () {
		while (true) {
			std::cout << "Doing work\n";
			sleep(1);
		}
	} };
	sleep(5);
	t.join(); // 线程t一直运行
}


void test_jthread01() {
	std::jthread jt{[] (){
		while (true) {
			std::cout << "Doing work\n";
			sleep(1);
		}
	}};
	sleep(5);
	jt.join(); // 线程jt一直运行
}

void test_jthread02() {
	std::jthread jt{ [] () {
		while (true) {
			std::cout << "Doing work\n";
			sleep(1);
		}
	} };
	sleep(5);
	jt.request_stop(); // 请求jt停止运行，但jt中没有接受停止请求
	jt.join();
}

void test_jthread03() {
	std::jthread jt{ [](std::stop_token st) {
		while (!st.stop_requested()) { // 有停止线程请求的处理
			std::cout << "Doing work\n";
			sleep(1);
		}
	} };
	sleep(5);
	jt.request_stop(); // 请求线程停止，因有响应停止请求而终止线程
	jt.join();
}

void test_jthread_jianshu01() {
	//test_thread01();
	//test_jthread01();
	//test_jthread02();
	test_jthread03();
}