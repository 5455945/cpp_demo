#pragma once

#include <condition_variable>
#include <list>
#include <iostream>
#include <mutex>
#include <thread>

void test05_03();

template <typename T>
class SyncQueue {
private:
	std::list<T> m_queue;   // 缓冲区队列
	std::mutex m_mutex;                 // 互斥量和条件变量结合使用
	std::condition_variable_any m_notEmpty; // 不为空的条件变量
	std::condition_variable_any m_notFull;  // 没有满的条件变量
	int m_maxSize;                          // 同步队列最大的size
	
	bool IsFull() const {
		return m_queue.size() == m_maxSize;
	}

	bool IsEmpty() const {
		return m_queue.empty();
	}

public:
	SyncQueue(int maxSize) : m_maxSize(maxSize) {}

	void Put(const T& x) {
		std::lock_guard<std::mutex> locker(m_mutex);
		while (IsFull()) {
			std::cout << "缓冲区满了，需要等待..." << std::endl;
			m_notFull.wait(m_mutex);
		}
		m_queue.push_back(x);
		m_notEmpty.notify_one();
	}

	void Take(T& x) {
		std::lock_guard<std::mutex> locker(m_mutex);
		while (IsEmpty()) {
			std::cout << "缓冲区空了，需要等待..." << std::endl;
			m_notEmpty.wait(m_mutex);
		}
		x = m_queue.front();
		m_queue.pop_front();
		m_notFull.notify_one();
	}

	bool Empty() {
		std::lock_guard<std::mutex> locker(m_mutex);
		return m_queue.empty();
	}

	bool Full() {
		std::lock_guard<std::mutex> locker(m_mutex);
		return m_queue.size() == m_maxSize;
	}

	size_t Size() {
		std::lock_guard<std::mutex> locker(m_mutex);
		return m_queue.size();
	}
};

template <typename T>
class SimpleSyncQueue {
private:
	std::list<T> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_notEmpty;

public:
	SimpleSyncQueue() {}

	void Put(const T& x) {
		std::lock_guard<std::mutex> locker(m_mutex);
		m_queue.push_back(x);
		m_notEmpty.notify_one();
	}

	void Take(T& x) {
		std::unique_lock<std::mutex> locker(m_mutex);
		m_notEmpty(locker, [this]() {return !m_queue.empty(); });
		x = m_queue.front();
		m_queue.pop_front();
	}

	bool Empty() {
		std::lock_guard<std::mutex> locker(m_mutex);
		return m_queue.empty();
	}

	size_t Size() {
		std::lock_guard<std::mutex> locker(m_mutex);
		return m_queue.size();
	}
};