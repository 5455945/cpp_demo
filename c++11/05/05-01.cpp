#include "05-01.h"
#include <iostream>
#include <string>
#include <vector>
#include <thread>

// 5.1 �߳�
// 5.1.1 �̵߳Ĵ���

void func05_01() {
	// do some work
	std::cout << "func05_01: do some work." << std::endl;
}

// �߳����в��ȴ��߳����н���
void test05_1_1() {
	std::thread t(func05_01);
	// join()���������̣߳�ֱ���̺߳���ִ�н���
	t.join();
}

void test05_1_2() {
	std::thread t(func05_01);
	// detach()���̺߳��̶߳�����룬���߳���Ϊ��̨�߳�ȥִ�У���ǰ�̲߳��ᱻ����
	// ����detach()֮��t���޷������̺߳�������ϵ�ˡ�
	t.detach(); // t.detach()ʹ��func05_01�ں�̨����
	std::cout << "test05_1_2:��������������" << std::endl;
}

// �߳̿��Խ������������
void func05_02(int i, double d, const std::string& s) {
	std::cout << "func05_02: " << i << ", " << d << ", " << s << std::endl;
}
void test05_1_3() {
	std::thread t(func05_02, 1, 2, "test");
	t.join();
}

// �߳̿����ƶ������ܸ���
void test05_1_4() {
	std::thread t(func05_01);
	std::thread t1(std::move(t));
	//t.join(); // ������ʱt�Ѿ�ʧЧ
	// joinable���ڼ��thread�Ƿ���Ҫjoin��joinableΪfalse�������3��:1.thread���ù�detach; 2.thread�Ѿ�join��; 3.threadΪ�ա�
	if (t.joinable()) {
		t.join();
	}
	t1.join();
}

// ͨ��std::bind��lambda���ʽ�������߳�
void func05_03(int a, double b) {
	std::cout << "func05_03: " << a << ", " << b << std::endl;
}
void test05_1_5() {
	std::thread t1(std::bind(func05_03, 1, 2));
	std::thread t2([](int a, double b) {}, 1, 2);
	t1.join();
	t2.join();
}

// ��Ҫע���̵߳���������
// ��Ҫ��֤�̺߳����������������̱߳���std::thread����������֮��
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

// ���̶߳��󱣴���������
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

// 5.1.2 �̵߳Ļ����÷�
// 1.��ȡ��ǰ��Ϣ
void test05_1_8() {
	std::thread t(func05_01);
	std::cout << "test05_1_8: get_id() a " << t.get_id() << std::endl;
	// ��ȡcpu�����������ȡʧ�ܷ���0
	std::cout << "test05_1_8: cpu����: " << std::thread::hardware_concurrency() << std::endl;
	t.join();
	std::cout << "test05_1_8: get_id() b " << t.get_id() << std::endl;
}

// 2.�߳�����
void func05_05() {
	std::this_thread::sleep_for(std::chrono::seconds(1)); // ����1��
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
	//// �쳣���̶߳��������̺߳�������
	//// �̶߳���t�Ѿ����٣��߳�func05_04�������У���func05_04���н���,����ջʱ�����쳣
    //test05_1_6();
	test05_1_7();
	test05_1_8();
	test05_1_9();
	return;
}
