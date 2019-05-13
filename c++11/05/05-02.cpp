#include "05-02.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

// 5.2 ������
// ��������һ��ͬ��ԭ���һ���߳�ͬ���ֶΣ������������߳�ͬʱ���ʵĹ�������
// C++11�����4�ֻ�����(mutex)
// std::mutex:��ռ�Ļ�����,���ܵݹ�ʹ�ã�
// std::time_mutex:����ʱ�Ķ�ռ�����������ܵݹ�ʹ�ã�
// std::recursive_mutex:�ݹ黥������������ʱ���ܣ�
// std::recursive_timed_mutex:����ʱ�ĵݹ黥����

// 5.2.1 ��ռ������std::mutex

// std::mutex�����÷�
std::mutex g_lock;
void func05_02_01() {
	g_lock.lock();  // ����������
	std::cout << "entered thread " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "leaving thread " << std::this_thread::get_id() << std::endl;
	g_lock.unlock(); // ����������
}
void test05_02_01() {
	std::thread t1(func05_02_01);
	std::thread t2(func05_02_01);
	std::thread t3(func05_02_01);
	t1.join();
	t2.join();
	t3.join();
}

// lock_guard()���Լ�lock/unlockд����lock_guard�ڹ���ʱ�Զ��������������˳�������ʱ��������������������
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

// 5.2.2 �ݹ黥����std::recursive_mutex
// �ݹ黥��������ͬһ�̶߳�λ�øû����������Խ��ͬһ�߳���Ҫ��λ�ȡ������ʱ�������⡣

// ʹ��std::mutex��ͬһ�̶߳�λ�ȡͬһ������������������
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
			mul(x); // �ٴλ�ȡmutexʱ����������,std::system_error
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

// ʹ��std::recursive_mutex����ͬһ�̶߳�λ�ȡ������
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
		mul(x);  // ͬһ�߳̿��Զ�λ�ȡͬһ�����������ᷢ���쳣
		div(y);  // ͬһ�߳̿��Զ�λ�ȡͬһ�����������ᷢ���쳣
	}
};
void test05_02_04() {
	Complex02 complex02;
	complex02.both(32, 23);
}

// ע�⣺������Ҫʹ�õݹ黥����
// a �ݹ黥����һ����Բ��ö�ռ��������
// b �ݹ黥����Ч�ʱض�ռ������Ч�ʵ�
// c �ݹ黥����û��˵���ݹ���ȣ�����һ���������ܻ��׳�std::system_error�쳣

// 5.2.3 ����ʱ�Ļ�����std::timed_mutex��std::recursive_timed_mutex
// ����ʱ�Ļ�������try_lock_for/try_lock_until�ӿ�
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