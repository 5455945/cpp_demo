#include "05-02.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

// 5.2 互斥量
// 互斥量是一种同步原语，是一种线程同步手段，用来保护多线程同时访问的共享数据
// C++11中提高4种互斥量(mutex)
// std::mutex:独占的互斥量,不能递归使用；
// std::time_mutex:带超时的独占互斥量，不能递归使用；
// std::recursive_mutex:递归互斥量，不带超时功能；
// std::recursive_timed_mutex:带超时的递归互斥量

// 5.2.1 独占互斥量std::mutex

// std::mutex基本用法
std::mutex g_lock;
void func05_02_01() {
	g_lock.lock();  // 锁定互斥量
	std::cout << "entered thread " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "leaving thread " << std::this_thread::get_id() << std::endl;
	g_lock.unlock(); // 解锁互斥量
}
void test05_02_01() {
	std::thread t1(func05_02_01);
	std::thread t2(func05_02_01);
	std::thread t3(func05_02_01);
	t1.join();
	t2.join();
	t3.join();
}

// lock_guard()可以简化lock/unlock写法，lock_guard在构造时自动锁定互斥量，退出作用域时进行析构，解锁互斥量
void func05_02_02() {
	std::lock_guard<std::mutex> locker(g_lock);
	std::cout << "entered thread " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "leaving thread " << std::this_thread::get_id() << std::endl;
}
void test05_02_02() {
	std::thread t1(func05_02_02);
	std::thread t2(func05_02_02);
	std::thread t3(func05_02_02);
	t1.join();
	t2.join();
	t3.join();
}

// 5.2.2 递归互斥量std::recursive_mutex
// 递归互斥量允许同一线程多次获得该互斥量，可以解决同一线程需要多次获取互斥量时死锁问题。

// 使用std::mutex在同一线程多次获取同一互斥量发生死锁用例
struct Complex01 {
	std::mutex mutex;
	int i;
	Complex01() : i(0) {}

	void mul(int x) {
		std::lock_guard<std::mutex> lock(mutex);
		i *= x;
	}

	void div(int x) {
		std::lock_guard<std::mutex> lock(mutex);
		i /= x;
	}

	void both(int x, int y) {
		std::lock_guard<std::mutex> lock(mutex);
		try {
			mul(x); // 再次获取mutex时，发生死锁,std::system_error
			div(y);
		}
		catch (...) {
			std::cout << "both exception!" << std::endl;
		}
	}
};
void test05_02_03() {
	Complex01 complex01;
	complex01.both(32, 23);
}

// 使用std::recursive_mutex允许同一线程多次获取互斥量
struct Complex02 {
	std::recursive_mutex mutex;
	int i;

	Complex02() : i(0) {}

	void mul(int x) {
		std::lock_guard<std::recursive_mutex> lock(mutex);
		i *= x;
	}

	void div(int x) {
		std::lock_guard<std::recursive_mutex> lock(mutex);
		i /= x;
	}

	void both(int x, int y) {
		std::lock_guard<std::recursive_mutex> lock(mutex);
		mul(x);  // 同一线程可以多次获取同一互斥量，不会发生异常
		div(y);  // 同一线程可以多次获取同一互斥量，不会发生异常
	}
};
void test05_02_04() {
	Complex02 complex02;
	complex02.both(32, 23);
}

// 注意：尽量不要使用递归互斥量
// a 递归互斥量一般可以采用独占互斥量简化
// b 递归互斥量效率必独占互斥量效率低
// c 递归互斥量没有说明递归深度，超过一定次数可能会抛出std::system_error异常

// 5.2.3 带超时的互斥量std::timed_mutex和std::recursive_timed_mutex
// 带超时的互斥量有try_lock_for/try_lock_until接口
std::timed_mutex mutex1;
void work1() {
	std::chrono::milliseconds timeout(100);
	while (true) {
		if (mutex1.try_lock_for(timeout)) {
			std::cout << std::this_thread::get_id() << ": do work with mutex" << std::endl;
			std::chrono::milliseconds sleepDuration(350);
			std::this_thread::sleep_for(sleepDuration);
			mutex1.unlock();
			break;
		}
		else {
			std::cout << std::this_thread::get_id() << ": do work without mutex" << std::endl;
			std::chrono::milliseconds sleepDuration(100);
			std::this_thread::sleep_for(sleepDuration);
		}
	}
}
void test05_02_05() {
	std::thread t1(work1);
	std::thread t2(work1);
	t1.join();
	t2.join();
}

void work(std::timed_mutex& mutex) {
	std::chrono::milliseconds timeout(100);
	while (true) {
		if (mutex.try_lock_for(timeout)) {
			std::cout << std::this_thread::get_id() << ": do work with mutex" << std::endl;
			std::chrono::milliseconds sleepDuration(350);
			std::this_thread::sleep_for(sleepDuration);
			mutex.unlock();
			break;
		}
		else {
			std::cout << std::this_thread::get_id() << ": do work without mutex" << std::endl;
			std::chrono::milliseconds sleepDuration(100);
			std::this_thread::sleep_for(sleepDuration);
		}
	}
}
void test05_02_06() {
	std::timed_mutex mutex;
	std::thread t1(work, std::ref(mutex));
	std::thread t2(work, std::ref(mutex));
	t1.join();
	t2.join();
}

void test05_02() {
	test05_02_01();
	test05_02_02();
	test05_02_03();
	test05_02_04();
	test05_02_05();
	test05_02_06();

	return;
}