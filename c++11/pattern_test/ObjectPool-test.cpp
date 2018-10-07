#include <ObjectPool.hpp>
#include <iostream>
#include <string>

struct BigObject {
	BigObject() {}
	BigObject(int a) {}
	BigObject(const int& a, const int& b) {}
	void Print(const std::string& str) {
		std::cout << str << std::endl;
	}
};

void Print(shared_ptr<BigObject> p, const std::string& str) {
	if (p != nullptr) {
		p->Print(str);
	}
}

void TestObjPool() {
	ObjectPool<BigObject> pool;
	pool.Init(2);  // 初始化对象池，初始创建两个对象
	{
		auto p = pool.Get();
		Print(p, "p");
		auto p2 = pool.Get();
		Print(p2, "p2");
	} // 出了作用域之后，对象池返回出来的对象又会自动回收

	auto p = pool.Get();
	auto p2 = pool.Get();
	Print(p, "p");
	Print(p2, "p2");

	// 对象池支持重载构造函数
	pool.Init(2, 1);
	auto p4 = pool.Get<int>();
	Print(p4, "p4");
	pool.Init(2, 1, 2);
	auto p5 = pool.Get<int, int>();
	Print(p5, "p5");
}
