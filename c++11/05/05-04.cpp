#include "05-04.h"

#include <atomic>
#include <iostream>
#include <string>
#include <mutex>

// 5.4 原子变量
// C++11提供一个原子类型std::atomic<T>，原子变量不需要使用互斥量来保护该变量

// 使用mutex实现的计数器
struct Counter1 {
	int value;
	std::mutex mutex;

	Counter1() :value(0) {}
	
	void increment() {
		std::lock_guard<std::mutex> locker(mutex);
		std::cout << "Counter1::increment()" << std::endl;
		++value;
	}

	void decrement() {
		std::lock_guard<std::mutex> locker(mutex);
		std::cout << "Counter1::decrement()" << std::endl;
		--value;
	}

	int get() {
		//std::lock_guard<std::mutex> locker(mutex);
		return value;
	}
};

// 用原子变量实现的计数器
struct AtomicCounter {
	std::atomic<int> value { 0 };

	void increment() {
		++value;
	}

	void decrement() {
		--value;
	}

	int get() {
		return value.load();
	}
};

void test05_04_01() {
	std::cout << "test05_04_01: start" << std::endl;
	Counter1 c1;
	std::thread t1([&]() {for (int i = 0; i < 100; i++) { c1.increment(); }});
	std::thread t2([&]() {for (int i = 0; i < 100; i++) { c1.decrement(); }});
	t1.join();
	t2.join();
	std::cout << "test05_04_01: " << c1.get() << std::endl;
}

void test05_04_02() {
	std::cout << "test05_04_02: start" << std::endl;
	AtomicCounter ac1;
	std::thread t1([&]() {for (int i = 0; i < 100; i++) { ac1.increment(); }});
	std::thread t2([&]() {for (int i = 0; i < 100; i++) { ac1.decrement(); }});
	t1.join();
	t2.join();
	std::cout << "test05_04_02: " << ac1.get() << std::endl;
}

void test05_04_03() {
	std::atomic<int> as(0);
	as.store(1);
	std::cout << as.load() << std::endl;
	int as2(2);
	as.exchange(as2);
	std::cout << as << std::endl;
	as.store(as2);
	std::cout << as.load() << std::endl;

	// 原子性加减通常是用CAS(Compare and Swap)完成的，与平台相关。CAS的基本形式是：CAS(addr,old,new),当addr中存放的值等于old时，用new对其替换
	// std::atomic::compare_exchange_weak
	// std::atomic::compare_exchange_strong
	//memory_order_relaxed Relaxed                 No synchronization of side effects.
	//memory_order_consume Consume                 Synchronizes the visible side effects on values carrying dependencies from the last release or sequentially consistent operation.
	//memory_order_acquire Acquire                 Synchronizes all visible side effects from the last release or sequentially consistent operation.
	//memory_order_release Release                 Synchronizes side effects with the next consume or acquire operation.
	//memory_order_acq_rel Acquire/Release         Reads as an acquire operation and writes as a release operation(as described above).
	//memory_order_seq_cst Sequentially-consistent Synchronizes all visible side effects with the other sequentially consistent operations, following a single total order.

}

void test05_04() {
	test05_04_01();
	test05_04_02();
	test05_04_03();
	return;
}