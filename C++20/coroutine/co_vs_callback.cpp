// https://github.com/franktea/temp/blob/master/uncategorized/co_vs_callback.cpp
// https://github.com/franktea/temp/blob/master/uncategorized/coroutine.md
#include <iostream>
#include <thread>
#include <experimental/coroutine>
#include <chrono>
#include <functional>

#include "co_vs_callback.h"

 // clang++ -std=c++2a -fcoroutines-ts -lstdc++ co_vs_callback.cpp

using call_back = std::function<void(int)>;
void Add100ByCallback(int init, call_back f) // 异步调用
{
	std::thread t([init, f]() {
		std::this_thread::sleep_for(std::chrono::seconds(5));
		std::cout << "Add100ByCallback: " << init << std::endl;
		f(init + 100);
		});
	t.detach();
}

struct Add100Awaitable
{
	Add100Awaitable(int init) :init_(init) {}
	bool await_ready() const { return false; }
	int await_resume() { return result_; }
	void await_suspend(std::experimental::coroutine_handle<> handle)
	{
		auto f = [handle, this](int value) mutable {
			result_ = value;
			handle.resume();
		};
		Add100ByCallback(init_, f); // 调用原来的异步调用
	}
	int init_;
	int result_;
};

struct Task
{
	struct promise_type {
		auto get_return_object() { return Task{}; }
		auto initial_suspend() { return std::experimental::suspend_never{}; }
		auto final_suspend() { return std::experimental::suspend_never{}; }
		void unhandled_exception() { std::terminate(); }
		void return_void() {}
	};
};

Task Add100ByCoroutine(int init, call_back f)
{
	int ret = co_await Add100Awaitable(init);
	//ret = co_await Add100Awaitable(ret);
	//ret = co_await Add100Awaitable(ret);
	f(ret);
}

void co_vs_callback()
{
	//Add100ByCallback(5, [](int value) { std::cout << "get result: " << value << "\n"; });
	Add100ByCoroutine(10, [](int value) { std::cout << "get result from coroutine1: " << value << "\n"; });
	//Add100ByCoroutine(20, [](int value) { std::cout << "get result from coroutine2: " << value << "\n"; });
	//Add100ByCoroutine(30, [](int value) { std::cout << "get result from coroutine3: " << value << "\n"; });
	//Add100ByCoroutine(40, [](int value) { std::cout << "get result from coroutine4: " << value << "\n"; });
	std::this_thread::sleep_for(std::chrono::seconds(50));
}