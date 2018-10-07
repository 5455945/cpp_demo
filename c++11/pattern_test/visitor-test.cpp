#include <visitor.hpp>
#include <iostream>
#include <string>

struct stA;
struct stB;

struct Base {
	// 定义通用的访问者类型，它可以访问stA和stB
	typedef Visitor<stA, stB> MyVisitor;
	virtual void Accept(MyVisitor&) = 0;
};

struct stA : Base
{
	double val;
	void Accept(Base::MyVisitor& v) {
		v.Visit(*this);
	}
};

struct stB : Base
{
	int val;
	void Accept(Base::MyVisitor& v) {
		v.Visit(*this);
	}
};

struct PrintVisitor : Base::MyVisitor {
	void Visit(const stA& a) {
		std::cout << "from stA: " << a.val << std::endl;
	}

	void Visit(const stB& b) {
		std::cout << "from stB: " << b.val << std::endl;
	}
};

void TestVisitor() {
	PrintVisitor vis;
	stA a;
	a.val = 8.97;
	stB b;
	b.val = 8;
	Base* base = &a;
	base->Accept(vis);
	base = &b;
	base->Accept(vis);
}
