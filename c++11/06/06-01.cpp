#include "06-01.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <iomanip>
#include <ctime>
#include <string>
// 6.1 处理日期和时间的chrono库

// 6.1.1 记录时长的duration
// duration表示一段时间间隔，用来记录时间长度
// template<class Rep, class Period = std::ratio<1,1>> class duration;
// template<std::intmax_t Num, std::intmax_t Denom = 1> class ratio;
void test06_01_01() {
	std::this_thread::sleep_for(std::chrono::seconds(3)); // 休眠3秒
	std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 休眠100毫秒

	std::chrono::milliseconds ms(3); // 3毫秒
	// 6000 microseconds constructed from 3 milliseconds
	std::chrono::microseconds us = 2 * ms; // 6000微秒
	// 30Hz clock using fractional ticks
	std::chrono::duration<double, std::ratio<1, 30>> hz30{ 3.5 };

	// 用count()获取时间间隔的时钟周期数
	std::cout << "3 ms duration has " << ms.count() << " ticks\n"
		<< "6000 us duration has " << us.count() << " ticks\n";

	// 时间间隔之间可以做差值计算
	std::chrono::minutes t1(10);
	std::chrono::seconds t2(60);
	std::chrono::seconds t3 = t1 - t2; // 这里会有自动单位转换
	std::cout << t3.count() << " second" << std::endl;

	// duration加减运算有一定规律
	// ratio<x1, y1> count1, ratio<x2, y2>,如果x1，x2的最大公约数为x;y1,y2的最大公倍数为y；
	// 则统一之后的ratio为ratio<x, y>
	std::chrono::duration<double, std::ratio<9, 7>> d1(3);
	std::chrono::duration<double, std::ratio<6, 5>> d2(1);
	auto d3 = d1 - d2;
	std::cout << typeid(d3).name() << std::endl;
	std::cout << d3.count() << std::endl;

	// 强制类型转换
	std::cout << std::chrono::duration_cast<std::chrono::minutes>(t3).count() << " minutes" << std::endl;
}

// 6.1.2 表示时间点的time point
// time_point表示一个时间点，用来获取从clock的纪元开始所经过duration(比如：可能是1970.1.1以来的时间间隔)和当前的时间间隔，
// time_point的函数time_from_eproch()用来获取1970年1月1日到time_point时间经过的duration
void test06_01_02() {
	using namespace std::chrono;
	typedef duration<int, std::ratio<60 * 60 * 24>> days_types;
	time_point<system_clock, days_types> today = time_point_cast<days_types>(system_clock::now());
	std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl;
}

// time_point的算术运算
void test06_01_03() {
	using namespace std::chrono;
	system_clock::time_point now = system_clock::now();
	std::time_t last = system_clock::to_time_t(now - hours(24));
	std::time_t next = system_clock::to_time_t(now + hours(24));

	std::cout << "One day ago, the time was " << std::put_time(std::localtime(&last), "%F %T") << std::endl;
	std::cout << "Next day, the time is " << std::put_time(std::localtime(&next), "%F %T") << std::endl;
}

// 6.1.3 获取系统始终的clocks
// clocks表示当前的系统时钟，内部有time_point,duration,Rep,Period等信息，主要
// 用来获取当前时间，以及实现time_t和time_point的相互转换。有如下3种时钟：
// system_clock:代表真实世界的时钟，具体时间值依赖于系统。system_clock保证提供的时间值是一个可读时间。
// steady_clock:不能被“调整”的时钟，并不一定代表真实世界的时间。保证先后调用now()得到的时间值不会递减。
// high_resolution_clock:高精度时钟，实际上是system_clock或者steady_clock的别名。
void test06_01_04() {
	std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
	std::cout << "Hello\n";
	std::chrono::system_clock::time_point t2 = std::chrono::system_clock::now();
	std::cout << (t2 - t1).count() << " tick count" << std::endl;

	// 通过时钟获取两个时间点之间相差多少个时钟周期，可以通过duration_cast将其转换为其它的时钟周期的duration。
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " microseconds" << std::endl;

	// system_clock的to_time_t方法可以将一个time_point转换为ctime
	// system_clock的from_time_t方法将ctime转换为time_point
	std::time_t now_c = std::chrono::system_clock::to_time_t(t2);
	std::chrono::system_clock::time_point pt2 = std::chrono::system_clock::from_time_t(now_c);

	// system_clock和std::put_time配合可以格式化日期
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << std::put_time(std::localtime(&t), "%Y-%m-%d %X") << std::endl;
	std::cout << std::put_time(std::localtime(&t), "%Y-%m-%d %H.%M.%S") << std::endl;
}

// 6.1.4 计时器timer
void test06_01_05() {
	Timer t; // 开始计时
	std::cout << "test06_01_05() start" << std::endl;
	std::cout << t.elapsed() << std::endl;
	std::cout << t.elapsed_micro() << std::endl;
	std::cout << t.elapsed_nano() << std::endl;
	std::cout << t.elapsed_seconds() << std::endl;
	std::cout << t.elapsed_minutes() << std::endl;
	std::cout << t.elapsed_hours() << std::endl;
}

// 6.2 数值类型和字符串的相互转换
void test06_02_01() {
	double f = 1.53;
	std::string f_str = std::to_string(f);
	std::cout << f_str << std::endl;

	double f1 = 4.125;
	std::wstring f_str1 = std::to_wstring(f1);
	std::wcout << f_str1 << std::endl;
}

void test06_02_02() {
	const char *str1 = "10";
	const char *str2 = "3.14159";
	const char *str3 = "31337 with words";
	const char *str4 = "words and 2";

	int num1 = std::atoi(str1);
	int num2 = std::atoi(str2);

	int num3 = std::atoi(str3);
	int num4 = std::atoi(str4);

	std::cout << "std::atoi(\"" << str1 << "\") is " << num1 << std::endl;
	std::cout << "std::atoi(\"" << str2 << "\") is " << num2 << std::endl;
	std::cout << "std::atoi(\"" << str3 << "\") is " << num3 << std::endl;
	std::cout << "std::atoi(\"" << str4 << "\") is " << num4 << std::endl;
}

// 6.3 宽窄字符转换
// C++11中增加了codecvt，但是在C++20中移除了
#include <codecvt>
void test06_03_01() {
	std::wstring str = L"中国人";
	std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> converter(new std::codecvt<wchar_t, char, std::mbstate_t>("CHS"));
	std::string narrowStr = converter.to_bytes(str);
	// string转wstring
	std::wstring wstr = converter.from_bytes(narrowStr);
	std::cout << narrowStr << std::endl;
	std::wcout.imbue(std::locale("chs")); // 初始化cout为中文输出
	std::wcout << wstr << std::endl;
}

void test06() {
	test06_01_01();
	test06_01_02();
	test06_01_03();
	test06_01_04();
	test06_01_05();
	test06_02_01();
	test06_02_02();
	test06_03_01();
	return;
}
