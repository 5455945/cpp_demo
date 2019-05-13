#pragma once
#include <chrono>

void test06();

class Timer {
public:
	Timer() : m_begin(std::chrono::high_resolution_clock::now()) {};
	void reset() { m_begin = std::chrono::high_resolution_clock::now(); }

	// Ĭ���������
	template<typename Duration = std::chrono::milliseconds>
	int64_t elapsed() const {
		return std::chrono::duration_cast<Duration>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}

	// ΢��
	int64_t elapsed_micro() const {
		return elapsed<std::chrono::microseconds>();
	}

	// ����
	int64_t elapsed_nano() const {
		return elapsed<std::chrono::nanoseconds>();
	}

	// ��
	int64_t elapsed_seconds() const {
		return elapsed<std::chrono::seconds>();
	}

	// ��
	int64_t elapsed_minutes() const {
		return elapsed<std::chrono::minutes>();
	}

	// ʱ
	int64_t elapsed_hours() const {
		return elapsed<std::chrono::hours>();
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
};