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
	pool.Init(2);  // ��ʼ������أ���ʼ������������
	{
		auto p = pool.Get();
		Print(p, "p");
		auto p2 = pool.Get();
		Print(p2, "p2");
	} // ����������֮�󣬶���ط��س����Ķ����ֻ��Զ�����

	auto p = pool.Get();
	auto p2 = pool.Get();
	Print(p, "p");
	Print(p2, "p2");

	// �����֧�����ع��캯��
	pool.Init(2, 1);
	auto p4 = pool.Get<int>();
	Print(p4, "p4");
	pool.Init(2, 1, 2);
	auto p5 = pool.Get<int, int>();
	Print(p5, "p5");
}
