// C ++ 20�е����̣߳�jthread������
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
	t.join(); // �߳�tһֱ����
}


void test_jthread01() {
	std::jthread jt{[] (){
		while (true) {
			std::cout << "Doing work\n";
			sleep(1);
		}
	}};
	sleep(5);
	jt.join(); // �߳�jtһֱ����
}

void test_jthread02() {
	std::jthread jt{ [] () {
		while (true) {
			std::cout << "Doing work\n";
			sleep(1);
		}
	} };
	sleep(5);
	jt.request_stop(); // ����jtֹͣ���У���jt��û�н���ֹͣ����
	jt.join();
}

void test_jthread03() {
	std::jthread jt{ [](std::stop_token st) {
		while (!st.stop_requested()) { // ��ֹͣ�߳�����Ĵ���
			std::cout << "Doing work\n";
			sleep(1);
		}
	} };
	sleep(5);
	jt.request_stop(); // �����߳�ֹͣ��������Ӧֹͣ�������ֹ�߳�
	jt.join();
}

void test_jthread_jianshu01() {
	//test_thread01();
	//test_jthread01();
	//test_jthread02();
	test_jthread03();
}