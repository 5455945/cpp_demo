#include "05-07.h"
#include <iostream>
#include <thread>
#include <future>

// 5.7 �߳��첽��������async
// std::asyncԭ��:async(std::launch::async | std::launch::deferred, f, args...)
// ��һ������Ϊ�����̲߳��ԣ�
// std::launch::async:�ڵ���asyncʱ��ʼ�����߳�
// std::launch::deferred:����asyncʱ�������̣߳�ֱ��future������get����waitʱ�Ŵ����߳�
// �ڶ����������̺߳���
// �������������̺߳����Ĳ���

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
