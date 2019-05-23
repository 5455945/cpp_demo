#include "../aop/aspect.hpp"
#include "../aop/Timer.hpp"
#include "../aop/HelloProxy.h"
#include <iostream>
#include <string>
#include <functional>
#include <memory>

namespace {
using namespace std;
}
void TestProxy() {
	std::shared_ptr<IHello> hello = std::make_shared<HelloProxy>(new Hello());
	hello->Output("It is a test");
}

struct AA
{
	void Before(int i)
	{
		cout << "Before from AA " << i << endl;
	}
	void After(int i)
	{
		cout << "After from AA " << i << endl;
	}
};

struct BB
{
	void Before(int i)
	{
		cout << "Before from BB " << i << endl;
	}
	void After(int i)
	{
		cout << "After from BB " << i << endl;
	}
};

struct CC
{
	void Before()
	{
		cout << "Before from CC " << endl;
	}
	void After()
	{
		cout << "After from CC " << endl;
	}
};

struct DD
{
	void Before()
	{
		cout << "Before from DD " << endl;
	}
	void After()
	{
		cout << "After from DD " << endl;
	}
};

void GT()
{
	cout << "real GT function" << endl;
}

void HT(int a)
{
	cout << "real HT function: " << a << endl;
}

struct TimeElapsedAspect
{
	void Before(int i)
	{

	}
	void After(int i)
	{
		cout << "time elapsed: " << m_t.elapsed() - m_lastTime << endl;
	}
private:
	double m_lastTime;
	Timer m_t;
};

struct LoggingAspect
{
	void Before(int i)
	{
		cout << "entering" << endl;
	}

	void After(int i)
	{
		cout << "leaving" << endl;
	}
};

void foo(int a)
{
	cout << "real HT function: " << a << endl;
}

int main()
{
	TestProxy();

	//织入普通函数 
	function<void(int)> f = bind(&HT, placeholders::_1);
	Invoke<AA, BB>(function<void(int)>(bind(&HT, placeholders::_1)), 1);
	// 组合了两个切面AA,BB
	Invoke<AA, BB>(f, 1);

	// 织入普通函数
	Invoke<CC, DD>(&GT);
	Invoke<AA, BB, AA>(&HT, 1);
	// 织入lambda表达式
	Invoke<AA, BB>([](int i) {}, 1);
	Invoke<CC, DD>([] {});
	{
		cout << "--------------------" << endl;
		Invoke<LoggingAspect, TimeElapsedAspect>(&foo, 1);
		cout << "----------------------" << endl;
		Invoke<TimeElapsedAspect, LoggingAspect>(&foo, 1);
		cout << "--------------------" << endl;
	}

	return 0;
}
