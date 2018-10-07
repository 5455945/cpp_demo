#include <../thread_pool/ThreadPool.hpp>

void TestThdPool() {
	ThreadPool pool(2);

	std::thread thd1([&pool]() {
		for (int i = 0; i < 10; i++) {
			auto thdId = this_thread::get_id();
			pool.AddTask([thdId]() {std::cout << "ͬ�����߳�1���߳�Id:" << thdId << std::endl; });
		}
	});

	std::thread thd2([&pool]() {
		for (int i = 0; i < 10; i++) {
			auto thdId = this_thread::get_id();
			pool.AddTask([thdId]() { std::cout << "ͬ�����߳�2���߳�Id:" << thdId << std::endl; });
		}
	});

	this_thread::sleep_for(std::chrono::seconds(2));
	//getchar();
	pool.Stop();
	thd1.join();
	thd2.join();
}

int main() {
	TestThdPool();
	return 0;
}