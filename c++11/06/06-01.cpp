#include "06-01.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <iomanip>
#include <ctime>
#include <string>
// 6.1 �������ں�ʱ���chrono��

// 6.1.1 ��¼ʱ����duration
// duration��ʾһ��ʱ������������¼ʱ�䳤��
// template<class Rep, class Period = std::ratio<1,1>> class duration;
// template<std::intmax_t Num, std::intmax_t Denom = 1> class ratio;
void test06_01_01() {
	std::this_thread::sleep_for(std::chrono::seconds(3)); // ����3��
	std::this_thread::sleep_for(std::chrono::milliseconds(100)); // ����100����

	std::chrono::milliseconds ms(3); // 3����
	// 6000 microseconds constructed from 3 milliseconds
	std::chrono::microseconds us = 2 * ms; // 6000΢��
	// 30Hz clock using fractional ticks
	std::chrono::duration<double, std::ratio<1, 30>> hz30{ 3.5 };

	// ��count()��ȡʱ������ʱ��������
	std::cout << "3 ms duration has " << ms.count() << " ticks\n"
		<< "6000 us duration has " << us.count() << " ticks\n";

	// ʱ����֮���������ֵ����
	std::chrono::minutes t1(10);
	std::chrono::seconds t2(60);
	std::chrono::seconds t3 = t1 - t2; // ��������Զ���λת��
	std::cout << t3.count() << " second" << std::endl;

	// duration�Ӽ�������һ������
	// ratio<x1, y1> count1, ratio<x2, y2>,���x1��x2�����Լ��Ϊx;y1,y2����󹫱���Ϊy��
	// ��ͳһ֮���ratioΪratio<x, y>
	std::chrono::duration<double, std::ratio<9, 7>> d1(3);
	std::chrono::duration<double, std::ratio<6, 5>> d2(1);
	auto d3 = d1 - d2;
	std::cout << typeid(d3).name() << std::endl;
	std::cout << d3.count() << std::endl;

	// ǿ������ת��
	std::cout << std::chrono::duration_cast<std::chrono::minutes>(t3).count() << " minutes" << std::endl;
}

// 6.1.2 ��ʾʱ����time point
// time_point��ʾһ��ʱ��㣬������ȡ��clock�ļ�Ԫ��ʼ������duration(���磺������1970.1.1������ʱ����)�͵�ǰ��ʱ������
// time_point�ĺ���time_from_eproch()������ȡ1970��1��1�յ�time_pointʱ�侭����duration
void test06_01_02() {
	using namespace std::chrono;
	typedef duration<int, std::ratio<60 * 60 * 24>> days_types;
	time_point<system_clock, days_types> today = time_point_cast<days_types>(system_clock::now());
	std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl;
}

// time_point����������
void test06_01_03() {
	using namespace std::chrono;
	system_clock::time_point now = system_clock::now();
	std::time_t last = system_clock::to_time_t(now - hours(24));
	std::time_t next = system_clock::to_time_t(now + hours(24));

	std::cout << "One day ago, the time was " << std::put_time(std::localtime(&last), "%F %T") << std::endl;
	std::cout << "Next day, the time is " << std::put_time(std::localtime(&next), "%F %T") << std::endl;
}

// 6.1.3 ��ȡϵͳʼ�յ�clocks
// clocks��ʾ��ǰ��ϵͳʱ�ӣ��ڲ���time_point,duration,Rep,Period����Ϣ����Ҫ
// ������ȡ��ǰʱ�䣬�Լ�ʵ��time_t��time_point���໥ת����������3��ʱ�ӣ�
// system_clock:������ʵ�����ʱ�ӣ�����ʱ��ֵ������ϵͳ��system_clock��֤�ṩ��ʱ��ֵ��һ���ɶ�ʱ�䡣
// steady_clock:���ܱ�����������ʱ�ӣ�����һ��������ʵ�����ʱ�䡣��֤�Ⱥ����now()�õ���ʱ��ֵ����ݼ���
// high_resolution_clock:�߾���ʱ�ӣ�ʵ������system_clock����steady_clock�ı�����
void test06_01_04() {
	std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
	std::cout << "Hello\n";
	std::chrono::system_clock::time_point t2 = std::chrono::system_clock::now();
	std::cout << (t2 - t1).count() << " tick count" << std::endl;

	// ͨ��ʱ�ӻ�ȡ����ʱ���֮�������ٸ�ʱ�����ڣ�����ͨ��duration_cast����ת��Ϊ������ʱ�����ڵ�duration��
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " microseconds" << std::endl;

	// system_clock��to_time_t�������Խ�һ��time_pointת��Ϊctime
	// system_clock��from_time_t������ctimeת��Ϊtime_point
	std::time_t now_c = std::chrono::system_clock::to_time_t(t2);
	std::chrono::system_clock::time_point pt2 = std::chrono::system_clock::from_time_t(now_c);

	// system_clock��std::put_time��Ͽ��Ը�ʽ������
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << std::put_time(std::localtime(&t), "%Y-%m-%d %X") << std::endl;
	std::cout << std::put_time(std::localtime(&t), "%Y-%m-%d %H.%M.%S") << std::endl;
}

// 6.1.4 ��ʱ��timer
void test06_01_05() {
	Timer t; // ��ʼ��ʱ
	std::cout << "test06_01_05() start" << std::endl;
	std::cout << t.elapsed() << std::endl;
	std::cout << t.elapsed_micro() << std::endl;
	std::cout << t.elapsed_nano() << std::endl;
	std::cout << t.elapsed_seconds() << std::endl;
	std::cout << t.elapsed_minutes() << std::endl;
	std::cout << t.elapsed_hours() << std::endl;
}

// 6.2 ��ֵ���ͺ��ַ������໥ת��
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

// 6.3 ��խ�ַ�ת��
// C++11��������codecvt��������C++20���Ƴ���
#include <codecvt>
void test06_03_01() {
	std::wstring str = L"�й���";
	std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> converter(new std::codecvt<wchar_t, char, std::mbstate_t>("CHS"));
	std::string narrowStr = converter.to_bytes(str);
	// stringתwstring
	std::wstring wstr = converter.from_bytes(narrowStr);
	std::cout << narrowStr << std::endl;
	std::wcout.imbue(std::locale("chs")); // ��ʼ��coutΪ�������
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
