#include "../ioc/Ioc.hpp"
#include <iostream>
#include <string>

// 11.1 IoC����ʱʲô
// ֱ��������������Ե�����
void test001() { // C++11֮ǰ�ķ���
	struct Base {
		virtual void Func() {};
		virtual ~Base() {}
	};
	struct DerivedB : Base {
		void Func() override { std::cout << "call func in DerivedB" << std::endl; }
	};
	struct DerivedC : Base {
		void Func() override { std::cout << "call func in DerivedC" << std::endl; }
	};
	struct DerivedD : Base {
		void Func() override { std::cout << "call func in DerivedD" << std::endl; }
	};
	class A {
	public:
		A(Base* interfaceB) : m_interfaceB(interfaceB) {}
		void Func() { m_interfaceB->Func(); }
		~A() {
			if (m_interfaceB) {
				delete m_interfaceB;
				m_interfaceB = nullptr;
			}
		}
	private:
		Base* m_interfaceB;
	};
	// A����ֱ��������Base�ӿڶ���
	A* pa = new A(new DerivedB());
	pa->Func();
	delete pa;

	// �����Ҫ����ĳЩ����ȥ����A���󣬾Ͳ������
	std::string sCondition = "C";
	pa = nullptr;
	if (sCondition == "B") {
		pa = new A(new DerivedB());
	}
	else if (sCondition == "C") {
		pa = new A(new DerivedC());
	}
	else {
		pa = new A(new DerivedD());
	}
	// ��Base����չһ���µ���������ʱ������A���󲻵ò�����һ����֧
	// �������Բ�����ԭ����A����Ĵ���ֱ��������new�ⲿ����������Ӳ���롣
	pa->Func();
	delete pa;
	pa = nullptr;

	// ����ͨ������ģʽ����������
	struct Factory {
		static Base* Create(const std::string& condition) {
			if (condition == "B") {
				return new DerivedB();
			}
			else if (condition == "C") {
				return new DerivedC();
			}
			else if (condition == "D") {
				return new DerivedD();
			}
			else {
				return nullptr;
			}
		}
	};
	// ���Թ���ģʽЧ��
	std::string condition = "D";
	pa = new A(Factory::Create(condition)); // ͨ�������������Base����
	pa->Func();
	delete pa;
	pa = nullptr;
}

// 11.2 Ioc��������
// ���Կ����õĶ��󹤳�
// ���IocContainer1��2�㲻�㣺
// A:ֻ�ܴ����޲ζ���
// B:ֻ�ܴ���һ�ֽӿ����͵Ķ���
// ���ϣ���������еĶ�����Ҫ�õ����Ͳ��
void test002() {
	struct ICar {
		virtual ~ICar() {}
		virtual void test() const = 0;
	};
	struct Bus : ICar {
		Bus() {}
		void test() const { std::cout << "Bus::test()" << std::endl; }
	};
	struct Car : ICar {
		Car() {}
		void test() const { std::cout << "Car::test()" << std::endl; }
	};

	IocContainer1<ICar> carioc;
	carioc.RegisterType<Bus>("bus");
	carioc.RegisterType<Car>("car");
	std::shared_ptr<ICar> bus = carioc.ResolveShared("bus");
	bus->test();
	std::shared_ptr<ICar> car = carioc.ResolveShared("car");
	car->test();
}

// 11.3 ���Ͳ���ĳ��÷���
// ������͵ķ���:
// 1)ͨ����̬���������
// 2)ͨ��ģ�����������
// 3)ͨ��ĳ�������������������
// 4)ͨ��ĳ��ͨ���������������
// 5)ͨ���հ���������
#include "../pattern/Variant.hpp"
#include <vector>
#include <string>
template<typename T>
void Func11_003(T t) {
	std::cout << t << std::endl;
}
void test003() {
	// ����ͨ�����ͣ�������Ϳ����ɶ�������
	typedef Variant<double, float, int, uint32_t, std::string> Value;
	std::vector<Value> vt; // ͨ�����͵�����������������������������Ͷ���
	vt.push_back(1);
	vt.push_back(std::string("test"));
	vt.push_back(1.22f);
	std::cout << vt[0].Get<int>() << ", " << vt[1].Get<std::string>() << ", " << vt[2].Get<float>() << std::endl;;

	// ʹ��Any��������
	std::vector<Any> v1;
	v1.push_back(1);
	v1.push_back("test");
	v1.push_back(2.35);
	auto r1 = v1[0].AnyCast<int>();
	auto r2 = v1[1].AnyCast<const char*>();
	auto r3 = v1[2].AnyCast<double>();
	std::cout << r1 << " " << r2 << " " << r3 << std::endl;

	Any a = 1;        // ���͸�ֵ��Any
	Any b = 1.25;     // double��ֵ��Any
	Any c = "string"; // �ַ�����ֵ��Any
	std::vector<Any> v2 = { a, b, c };
	auto f = [](Any& it) {
		if (it.Is<int>()) {
			std::cout << it.AnyCast<int>() << " ";
		}
		else if (it.Is<double>()) {
			std::cout << it.AnyCast<double>() << " ";
		}
		else if (it.Is<char *>()) {
			std::cout << it.AnyCast<char*>() << " ";
		}
		else if (it.Is<std::string>()) {
			std::cout << it.AnyCast<std::string>() << " ";
		}
	};
	for (auto& it : v2) {
		f(it);
	}
	std::cout << std::endl;
}

// 11.4 ͨ��Any�ͱհ����������
void test004() {
	// ͨ���հ����������
	int x = 1;
	char y = 's';
	// ���Ͳ�����հ������ؾ������ͣ����հ���������
	std::vector<std::function<void()>> v3;
	v3.push_back([x] {Func11_003(x); });
	v3.push_back([y] {Func11_003(y); });
	// �����հ����ӱհ���ȡ��ʵ�ʵĲ���������ӡ����
	for (auto& item : v3) {
		item();
	}
}
// ��Any������͵Ķ��󹤳��Ĳ��Դ���
void test005() {
	struct Bus {
		void test() const { std::cout << "Bus::test()" << std::endl; }
	};
	struct Car {
		void test() const { std::cout << "Car::test()" << std::endl; }
	};
	struct Base {
		virtual void Func() {};
		virtual ~Base() {};
	};
	struct DerivedB : Base {
		void Func() override { std::cout << "call func in DerivedB" << std::endl; }
	};
	struct DerivedC : Base {
		void Func() override { std::cout << "call func in DerivedC" << std::endl; }
	};
	struct DerivedD : Base {
		void Func() override { std::cout << "call func in DerivedD" << std::endl; }
	};
	struct A {
		A(Base* ptr) : m_ptr(ptr) {}
		~A() {
			if (m_ptr) {
				delete m_ptr;
				m_ptr = nullptr;
			}
		}
		void Func() { m_ptr->Func(); }
	private:
		Base* m_ptr;
	};

	IocContainer2 ioc;
	ioc.RegisterType<A, DerivedB>("B");
	ioc.RegisterType<A, DerivedC>("C");
	ioc.RegisterType<A, DerivedD>("D");
	auto pa1 = ioc.ResolveShared<A>("B");
	pa1->Func();
	auto pa2 = ioc.ResolveShared<A>("C");
	pa2->Func();
	ioc.RegisterType<Bus>("bus");
	ioc.RegisterType<Car>("car");
	auto bus = ioc.ResolveShared<Bus>("bus");
	bus->test();
	auto car = ioc.ResolveShared<Car>("car");
	car->test();
}

// 11.5 ������������
// Ioc���������������������ַ�ʽ
// A:ͨ��IoC��������������ϵ����ͨ��IoC����������������
// B:ͨ������������������ϵ����ͨ��IoC����������������
void test006() {
	struct Base {
		virtual void Func() = 0;
		virtual ~Base() { }
	};
	struct Derived : public Base {
		void Func() { std::cout << __FUNCTION__ << std::endl; }
	};
	struct Derived2 :public Base {
		void Func() { std::cout << __FUNCTION__ << std::endl; }
	};
	struct Derived3 :public Base {
		void Func() { std::cout << __FUNCTION__ << std::endl; }
	};
	struct A {
		A(Base* ptr) : m_ptr(ptr) {}
		~A() {
			if (m_ptr) {
				delete m_ptr;
				m_ptr = nullptr;
			}
		}
		void Func() { m_ptr->Func(); }

	private:
		Base* m_ptr;
	};
	
	IocContainer2 ioc;

	// A:ͨ��IoC��������������ϵ
	ioc.RegisterType<A, Derived>();   // ����������ϵ
	auto pa = ioc.ResolveShared<A>(); // ͨ��IoC��������Ŀ���������������
	pa->Func();

	// B:����������������ϵ
	ioc.RegisterType<Base, Derived>("drived");
	ioc.RegisterType<Base, Derived2>("drived2");
	ioc.RegisterType<Base, Derived3>("drived3");
	auto d0 = ioc.ResolveShared<Base>("drived");  // �����ݲ������ô���Derived2����
	auto d1 = ioc.ResolveShared<Base>("drived2"); // �����ݲ������ô���Derived2����
	auto d2 = ioc.ResolveShared<Base>("drived3"); // �����ݲ������ô���Derived3����
	d0->Func();
	d1->Func();
	d2->Func();
}
// 11.7 ������IoC����
// ���󹤳����Դ���
void test007() {
	struct Base {
		virtual void Func() = 0;
		virtual ~Base() {}
	};
	struct DerivedB :Base {
		DerivedB(int a, double b) :m_a(a), m_b(b) {}
		void Func() override { std::cout << __FUNCTION__ << ": " << m_a + m_b << std::endl; }
	private:
		int m_a;
		double m_b;
	};
	struct DerivedC : public Base { 
		void Func() override { std::cout << __FUNCTION__ << std::endl; }
	};
	struct A {
		A(Base* ptr) : m_ptr(ptr) {}
		void Func() { m_ptr->Func(); }
		~A() {
			if (m_ptr) {
				delete m_ptr;
				m_ptr = nullptr;
			}
		}
	private:
		Base* m_ptr;
	};
	IocContainer3 ioc;
	ioc.RegisterType<A, DerivedC>("C");
	auto c = ioc.ResolveShared<A>("C");
	c->Func();

	// ע��ʱҪע��DerivedB�Ĳ���int��double
	ioc.RegisterType<A, DerivedB, int, double>("B");
	auto b = ioc.ResolveShared<A>("B", 1, 2.0); // Ҫ�������
	b->Func();
}

// ֧�����õĶ��󹤳����Դ���
void test008() {
	struct Interface {
		virtual void Func() = 0;
		virtual ~Interface() {}
	};
	struct DerivedB : public Interface {
		void Func() override { std::cout << __FUNCTION__ << std::endl; }
	};
	struct DerivedC : public Interface{
		void Func() override { std::cout << __FUNCTION__ << std::endl; }
	};
    
	IocContainer ioc;
	// ���ýӿں�������Ĺ�ϵ������һ��Ψһ��key���ں���������keyѡ��Ҫ����������
	ioc.RegisterType<Interface, DerivedB>("B");
	ioc.RegisterType<Interface, DerivedC>("C");
	// ���ݲ�������������DerivedB
	std::shared_ptr<Interface> pb = ioc.ResolveShared<Interface>("B");
	pb->Func();
	// ���ݲ������ʹ������������DerivedC
	std::shared_ptr<Interface> pc = ioc.ResolveShared<Interface>("C");
	pc->Func();

	// ʹ�ò�ͬ��ע�ắ����ע��Derived����
	struct DerivedD {
		void Func(){ std::cout << __FUNCTION__ << std::endl; }
	};
	ioc.RegisterTypeSimple<DerivedD>("x");
	std::shared_ptr<DerivedD> pd = ioc.ResolveShared<DerivedD>("x");
	pd->Func();

	// ����
	struct Bus {
		void Func() const { std::cout << __FUNCTION__ << std::endl; }
	};
	struct Car {
		void Func() const { std::cout << __FUNCTION__ << std::endl; }
	};
	IocContainer ioc4;
	ioc4.RegisterTypeSimple<Bus>("bus");
	ioc4.RegisterTypeSimple<Car>("car");
	auto bus = ioc4.ResolveShared<Bus>("bus");
	bus->Func();
	auto car = ioc4.ResolveShared<Car>("car");
	car->Func();
}

// ���캯��������ע��
void test009() {
	struct IX {
		virtual void g() = 0;
		virtual ~IX() {}
	};
	class X : public IX {
	public:
		void g() { std::cout << "it is a test in x" << std::endl; }
	};
	class Y : public IX {
	public:
		Y(int a) : m_a(a) {}
		void g() { std::cout << "it is a test in y : " << m_a << std::endl; }
	private:
		int m_a;
	};
	struct MyStructA {
		MyStructA(IX* x) : m_x(x) {}
		~MyStructA() {
			if (m_x != nullptr) {
				delete m_x;
				m_x = nullptr;
			}
		}
		void Fun() { m_x->g(); }
	private:
		IX* m_x;
	};

	// ʹ�ýӿڴ�����������
	MyStructA* pa = new MyStructA(new X()); // ֱ�Ӵ�������
	pa->Fun();

	// ʹ��IoC������������
	IocContainer ioc;
	ioc.RegisterType<MyStructA, X>("A");  // ����������ϵ
	// ͨ��IoC����ȥ����Ŀ���������������
	auto px = ioc.ResolveShared<MyStructA>("A");
	px->Fun();
	ioc.RegisterType<MyStructA, Y, int>("B"); // ������ע�ắ�����ͣ�����Ҫ��ʵ��
	auto py = ioc.ResolveShared<MyStructA, int>("B", 25); // ������Ҫ����������Ҫ��ʵ��
	py->Fun();
}

int main() {
	test001();
	test002();
	test003();
	test004();
	test005();
	test006();
	test007();
	test008();
	test009();
    return 0;
}