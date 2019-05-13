#include "05-06.h"
#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <utility>

// 5.6.1 获取线程函数返回值的类std::future
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

// 5.6.2 协助线程赋值的类std::promise
void test05_06_01() {
	std::promise<int> pr;
	std::future<int> f = pr.get_future();
	std::thread t([](std::promise<int>& p) { p.set_value(9); }, std::ref(pr));
	int r = f.get();
	t.join();
	std::cout << "test05_06_01: " << r << std::endl;
}

// 5.6.3 可调用兑现的包装类std::packaged_task
void test05_06_02() {
	std::packaged_task<int()> task([]() {return 7; });
	std::thread t1(std::ref(task));
	std::future<int> f1 = task.get_future();
	t1.join();
	int r1 = f1.get();
	std::cout << "test05_06_02: " << r1 << std::endl;
}

// 来自https://zh.cppreference.com/w/cpp/thread/future
void test05_06_03(){
    // 来自 packaged_task 的 future
	std::packaged_task<int()> task([]() { return 7; }); // 包装函数
	std::future<int> f1 = task.get_future();  // 获取 future
	std::thread(std::move(task)).detach();    // 在后台运行

	// 来自 async() 的 future
	std::future<int> f2 = std::async(std::launch::async, []() { return 8; });

	// 来自 promise 的 future
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

// 5.6.4 std::promise,std::packaged_task和std::future三者关系
int func05_06_01(int x) { return x + 2; }
void test05_06_04() {
	std::packaged_task<int(int)> tsk(func05_06_01);
	std::future<int> fut = tsk.get_future();  // 获取future

	std::thread(std::move(tsk), 2).detach();  // tsk作为线程函数

	int value = fut.get();  // 等待tsk完成并获取结果
	std::cout << "The result is " << value << std::endl;

	// std::future是不能复制的，不能放在容器中,可以使用shared_future
	std::vector<std::shared_future<int>> v;
	auto f = std::async(std::launch::async, [](int a, int b) {return a + b; }, 2, 3);
	std::cout << "std::async的返回类型：" << typeid(f).name() << std::endl;
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

	// packaged_task 的定义，相当于定义函数体
	std::packaged_task<void(int a, const std::string& b)> task([](int a, const std::string& b){ std::cout << a << " " << b << std::endl; });
	// task和线程绑定时，相当于要调用函数，需要提供实参
	std::thread t2(std::ref(task), 3, "bbbb");
	// 获取和task相关的future变量
	std::future<void> f2 = task.get_future();
	t2.join(); // 等待线程完成
	//f2.wait(); // 对future进行处理，这里因为是void类型，也可以省去
}

void test05_06() {
	test05_06_01();
	test05_06_02();
	test05_06_03();
	test05_06_04();
	test01();
	return;
}