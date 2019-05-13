#include "05-01.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread>

// 5.1 线程
// 5.1.1 线程的创建

void func05_01() {
	// do some work
	std::cout << "func05_01: do some work." << std::endl;
}

// 线程运行并等待线程运行结束
void test05_1_1() {
	std::thread t(func05_01);
	// join()将会阻塞线程，直到线程函数执行结束
	t.join();
}

void test05_1_2() {
	std::thread t(func05_01);
	// detach()将线程和线程对象分离，让线程作为后台线程去执行，当前线程不会被阻塞
	// 调用detach()之后，t就无法再与线程函数有联系了。
	t.detach(); // t.detach()使得func05_01在后台运行
	std::cout << "test05_1_2:继续做其它事情" << std::endl;
}

// 线程可以接收任意个参数
void func05_02(int i, double d, const std::string& s) {
	std::cout << "func05_02: " << i << ", " << d << ", " << s << std::endl;
}
void test05_1_3() {
	std::thread t(func05_02, 1, 2, "test");
	t.join();
}

// 线程可以移动，不能复制
void test05_1_4() {
	std::thread t(func05_01);
	std::thread t1(std::move(t));
	//t.join(); // 错误，这时t已经失效
	// joinable用于检测thread是否需要join。joinable为false的情况有3种:1.thread调用过detach; 2.thread已经join过; 3.thread为空。
	if (t.joinable()) {
		t.join();
	}
	t1.join();
}

// 通过std::bind或lambda表达式来创建线程
void func05_03(int a, double b) {
	std::cout << "func05_03: " << a << ", " << b << std::endl;
}
void test05_1_5() {
	std::thread t1(std::bind(func05_03, 1, 2));
	std::thread t2([](int a, double b) {}, 1, 2);
	t1.join();
	t2.join();
}

// 需要注意线程的生命周期
// 需要保证线程函数的生命周期在线程变量std::thread的生命周期之内
void func05_04() {
	std::cout << "func05_04: start" << std::endl;
	std::this_thread::sleep_for(std::chrono::microseconds(500));
	std::cout << "func05_04: end" << std::endl;
}
void test05_1_6() {
	std::cout << "test05_1_6: start" << std::endl;
	std::thread t(func05_04);
	std::cout << "test05_1_6: end" << std::endl;
}

// 把线程对象保存在容器中
std::vector<std::thread> g_list1;
std::vector<std::shared_ptr<std::thread>> g_list2;
void CreateThread() {
	std::thread t(func05_01);
	g_list1.emplace_back(std::move(t));
	g_list2.emplace_back(std::make_shared<std::thread>(func05_01));
}
void test05_1_7() {
	CreateThread();
	for (auto& t : g_list1) {
		t.join();
	}
	for (auto& t : g_list2) {
		t->join();
	}
}

// 5.1.2 线程的基本用法
// 1.获取当前信息
void test05_1_8() {
	std::thread t(func05_01);
	std::cout << "test05_1_8: get_id() a " << t.get_id() << std::endl;
	// 获取cpu核数，如果获取失败返回0
	std::cout << "test05_1_8: cpu核数: " << std::thread::hardware_concurrency() << std::endl;
	t.join();
	std::cout << "test05_1_8: get_id() b " << t.get_id() << std::endl;
}

// 2.线程休眠
void func05_05() {
	std::this_thread::sleep_for(std::chrono::seconds(1)); // 休眠1秒
	std::cout << "func05_05: timeout." << std::endl;
}
void test05_1_9() {
	std::thread t(func05_05);
	t.join();
}

void test05_01() {
	test05_1_1();
	test05_1_2();
	test05_1_3();
	test05_1_4();
	test05_1_5();
	//// 异常，线程对象先于线程函数结束
	//// 线程对象t已经销毁，线程func05_04还在运行，当func05_04运行结束,清理栈时发生异常
    //test05_1_6();
	test05_1_7();
	test05_1_8();
	test05_1_9();
	return;
}
