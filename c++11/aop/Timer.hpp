#pragma once
#include<chrono>
//using namespace std;
using namespace std::chrono;

class Timer
{
public:
	Timer() : m_begin(high_resolution_clock::now()) {}
	void reset() { m_begin = high_resolution_clock::now(); }

	//Ä¬ÈÏÊä³öºÁÃë
	int64_t elapsed() const
	{
		return duration_cast<chrono::milliseconds>(high_resolution_clock::now() - m_begin).count();
	}

	//Ä¬ÈÏÊä³öÃë
	double elapsed_second() const
	{
		return duration_cast<duration<double>>(high_resolution_clock::now() - m_begin).count();
	}

	//Î¢Ãë
	int64_t elapsed_micro() const
	{
		return duration_cast<chrono::microseconds>(high_resolution_clock::now() - m_begin).count();
	}

	//ÄÉÃë
	int64_t elapsed_nano() const
	{
		return duration_cast<chrono::nanoseconds>(high_resolution_clock::now() - m_begin).count();
	}

	//Ãë
    int64_t elapsed_seconds() const
	{
        return duration_cast<chrono::seconds>(high_resolution_clock::now() - m_begin).count();
    }
	
	//·Ö
	int64_t elapsed_minutes() const
	{
		return duration_cast<chrono::minutes>(high_resolution_clock::now() - m_begin).count();
	}

	//Ê±
	int64_t elapsed_hours() const
	{
		return duration_cast<chrono::hours>(high_resolution_clock::now() - m_begin).count();
	}

private:
	time_point<high_resolution_clock> m_begin;
};

