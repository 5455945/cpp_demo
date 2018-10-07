#include <iostream>
#include <string>
#include "Singleton.hpp"
using namespace std;

template <class T> T*  Singleton<T>::m_pInstance = nullptr;

struct A
{
	A(const string& x) { cout << "lvalue" << endl; }
	A(string && x) { cout << "rvalue" << endl; }
};

struct B
{
	B(const string&) { cout << "lvalue" << endl; }
	B(string && x) { cout << "rvalue" << endl; }
};

struct C
{
	C(int x, double y) {}
	void Fun() { cout << "test" << endl; }
};

class SingleTest
{
public:
	SingleTest(int x, double y) :m_iX(x), m_dY(y) {}
	double sum() { return m_iX + m_dY; }

private:
	int m_iX;
	double m_dY;
};

void test_Singleton() {
	string str = "bb";
	Singleton<A>::Instance(str);
	Singleton<B>::Instance(std::move(str));
	Singleton<C>::Instance(1, 3.14);

	Singleton<C>::GetInstance()->Fun();

	Singleton<A>::DestroyInstance();
	Singleton<B>::DestroyInstance();
	Singleton<C>::DestroyInstance();
}
