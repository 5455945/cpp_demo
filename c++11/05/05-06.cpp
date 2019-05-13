#include "05-06.h"
#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <utility>

// 5.6.1 ��ȡ�̺߳�������ֵ����std::future
void print_futrue(std::future<int>& future) {
	std::future_status status;
	do {
		status = future.wait_for(std::chrono::milliseconds(100));
		if (status == std::future_status::deferred) {
			std::cout << "defrred" << std::endl;
		}
		else if (status == std::future_status::timeout) {
			std::cout << "timeout" << std::endl;
		}
		else if (status == std::future_status::ready) {
			std::cout << "ready!" << std::endl;
		}
	} while (status != std::future_status::ready);
}

// 5.6.2 Э���̸߳�ֵ����std::promise
void test05_06_01() {
	std::promise<int> pr;
	std::future<int> f = pr.get_future();
	std::thread t([](std::promise<int>& p) { p.set_value(9); }, std::ref(pr));
	int r = f.get();
	t.join();
	std::cout << "test05_06_01: " << r << std::endl;
}

// 5.6.3 �ɵ��ö��ֵİ�װ��std::packaged_task
void test05_06_02() {
	std::packaged_task<int()> task([]() {return 7; });
	std::thread t1(std::ref(task));
	std::future<int> f1 = task.get_future();
	t1.join();
	int r1 = f1.get();
	std::cout << "test05_06_02: " << r1 << std::endl;
}

// ����https://zh.cppreference.com/w/cpp/thread/future
void test05_06_03(){
    // ���� packaged_task �� future
	std::packaged_task<int()> task([]() { return 7; }); // ��װ����
	std::future<int> f1 = task.get_future();  // ��ȡ future
	std::thread(std::move(task)).detach();    // �ں�̨����

	// ���� async() �� future
	std::future<int> f2 = std::async(std::launch::async, []() { return 8; });

	// ���� promise �� future
	std::promise<int> p;
	std::future<int> f3 = p.get_future();
	std::thread([&p] { p.set_value_at_thread_exit(9); }).detach();

	std::cout << "Waiting..." << std::flush;
	f1.wait();
	f2.wait();
	f3.wait();
	std::cout << "Done!\nResults are: "
	<< f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
}

// 5.6.4 std::promise,std::packaged_task��std::future���߹�ϵ
int func05_06_01(int x) { return x + 2; }
void test05_06_04() {
	std::packaged_task<int(int)> tsk(func05_06_01);
	std::future<int> fut = tsk.get_future();  // ��ȡfuture

	std::thread(std::move(tsk), 2).detach();  // tsk��Ϊ�̺߳���

	int value = fut.get();  // �ȴ�tsk��ɲ���ȡ���
	std::cout << "The result is " << value << std::endl;

	// std::future�ǲ��ܸ��Ƶģ����ܷ���������,����ʹ��shared_future
	std::vector<std::shared_future<int>> v;
	auto f = std::async(std::launch::async, [](int a, int b) {return a + b; }, 2, 3);
	std::cout << "std::async�ķ������ͣ�" << typeid(f).name() << std::endl;
	v.push_back(f.share());
	std::cout << "The shared_future result is " << v[0].get() << std::endl;
}
#include <string>
void test01() {
	std::promise<int> pr;
	std::thread t([](std::promise<int>& p) {p.set_value(2); }, std::ref(pr));
	std::future<int> f1 = pr.get_future();
	int r = f1.get();
	t.join();
	std::cout << r << std::endl;

	// packaged_task �Ķ��壬�൱�ڶ��庯����
	std::packaged_task<void(int a, const std::string& b)> task([](int a, const std::string& b){ std::cout << a << " " << b << std::endl; });
	// task���̰߳�ʱ���൱��Ҫ���ú�������Ҫ�ṩʵ��
	std::thread t2(std::ref(task), 3, "bbbb");
	// ��ȡ��task��ص�future����
	std::future<void> f2 = task.get_future();
	t2.join(); // �ȴ��߳����
	//f2.wait(); // ��future���д���������Ϊ��void���ͣ�Ҳ����ʡȥ
}

void test05_06() {
	test05_06_01();
	test05_06_02();
	test05_06_03();
	test05_06_04();
	test01();
	return;
}