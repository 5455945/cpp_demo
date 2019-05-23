#include "../ioc/Ioc.hpp"
#include <iostream>
#include <string>

// 11.1 IoC容器时什么
// 直接依赖产生耦合性的例子
void test001() { // C++11之前的方法
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
	// A对象直接依赖于Base接口对象
	A* pa = new A(new DerivedB());
	pa->Func();
	delete pa;

	// 如果需要根据某些条件去创建A对象，就产生耦合
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
	// 当Base再扩展一个新的派生类型时，创建A对象不得不增加一个分支
	// 这个耦合性产生的原因是A对象的创建直接依赖于new外部对象，这属于硬编码。
	pa->Func();
	delete pa;
	pa = nullptr;

	// 可以通过工厂模式来创建对象
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
	// 测试工厂模式效果
	std::string condition = "D";
	pa = new A(Factory::Create(condition)); // 通过工厂间接依赖Base对象
	pa->Func();
	delete pa;
	pa = nullptr;
}

// 11.2 Ioc创建对象
// 测试可配置的对象工厂
// 这个IocContainer1有2点不足：
// A:只能创建无参对象
// B:只能创建一种接口类型的对象
// 如果希望创建所有的对象，需要用到类型察除
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

// 11.3 类型察除的常用方法
// 察除类型的方法:
// 1)通过多态来察除类型
// 2)通过模板来察除类型
// 3)通过某种类型容器来察除类型
// 4)通过某种通用类型来察除类型
// 5)通过闭包类察除类型
#include "../pattern/Variant.hpp"
#include <vector>
#include <string>
template<typename T>
void Func11_003(T t) {
	std::cout << t << std::endl;
}
void test003() {
	// 定义通用类型，这个类型可容纳多种类型
	typedef Variant<double, float, int, uint32_t, std::string> Value;
	std::vector<Value> vt; // 通用类型的容器，这个容器可以容纳上述类型对象
	vt.push_back(1);
	vt.push_back(std::string("test"));
	vt.push_back(1.22f);
	std::cout << vt[0].Get<int>() << ", " << vt[1].Get<std::string>() << ", " << vt[2].Get<float>() << std::endl;;

	// 使用Any类察除类型
	std::vector<Any> v1;
	v1.push_back(1);
	v1.push_back("test");
	v1.push_back(2.35);
	auto r1 = v1[0].AnyCast<int>();
	auto r2 = v1[1].AnyCast<const char*>();
	auto r3 = v1[2].AnyCast<double>();
	std::cout << r1 << " " << r2 << " " << r3 << std::endl;

	Any a = 1;        // 整型赋值给Any
	Any b = 1.25;     // double赋值给Any
	Any c = "string"; // 字符串赋值给Any
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

// 11.4 通过Any和闭包来察除类型
void test004() {
	// 通过闭包来察除类型
	int x = 1;
	char y = 's';
	// 类型察除，闭包中隐藏具体类型，将闭包保存起来
	std::vector<std::function<void()>> v3;
	v3.push_back([x] {Func11_003(x); });
	v3.push_back([y] {Func11_003(y); });
	// 遍历闭包，从闭包中取出实际的参数，并打印出来
	for (auto& item : v3) {
		item();
	}
}
// 用Any察除类型的对象工厂的测试代码
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

// 11.5 创建依赖对象
// Ioc容器创建依赖对象有两种方式
// A:通过IoC容器配置依赖关系，并通过IoC容器创建依赖对象
// B:通过参数化配置依赖关系，并通过IoC容器创建依赖对象
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

	// A:通过IoC容器配置依赖关系
	ioc.RegisterType<A, Derived>();   // 配置依赖关系
	auto pa = ioc.ResolveShared<A>(); // 通过IoC容器创建目标对象及其依赖对象
	pa->Func();

	// B:参数化配置依赖关系
	ioc.RegisterType<Base, Derived>("drived");
	ioc.RegisterType<Base, Derived2>("drived2");
	ioc.RegisterType<Base, Derived3>("drived3");
	auto d0 = ioc.ResolveShared<Base>("drived");  // 将根据参数配置创建Derived2对象
	auto d1 = ioc.ResolveShared<Base>("drived2"); // 将根据参数配置创建Derived2对象
	auto d2 = ioc.ResolveShared<Base>("drived3"); // 将根据参数配置创建Derived3对象
	d0->Func();
	d1->Func();
	d2->Func();
}
// 11.7 完整的IoC容器
// 对象工厂测试代码
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

	// 注册时要注意DerivedB的参数int和double
	ioc.RegisterType<A, DerivedB, int, double>("B");
	auto b = ioc.ResolveShared<A>("B", 1, 2.0); // 要传入参数
	b->Func();
}

// 支持配置的对象工厂测试代码
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
	// 配置接口和派生类的关系，关联一个唯一的key，在后面根据这个key选择要创建的类型
	ioc.RegisterType<Interface, DerivedB>("B");
	ioc.RegisterType<Interface, DerivedC>("C");
	// 根据参数创建派生类DerivedB
	std::shared_ptr<Interface> pb = ioc.ResolveShared<Interface>("B");
	pb->Func();
	// 根据参数类型创建派生类对象DerivedC
	std::shared_ptr<Interface> pc = ioc.ResolveShared<Interface>("C");
	pc->Func();

	// 使用不同的注册函数，注册Derived类型
	struct DerivedD {
		void Func(){ std::cout << __FUNCTION__ << std::endl; }
	};
	ioc.RegisterTypeSimple<DerivedD>("x");
	std::shared_ptr<DerivedD> pd = ioc.ResolveShared<DerivedD>("x");
	pd->Func();

	// 再例
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

// 构造函数的依赖注入
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

	// 使用接口创建依赖对象
	MyStructA* pa = new MyStructA(new X()); // 直接创建依赖
	pa->Fun();

	// 使用IoC创建依赖对象
	IocContainer ioc;
	ioc.RegisterType<MyStructA, X>("A");  // 配置依赖关系
	// 通过IoC容器去创建目标对象及其依赖对象
	auto px = ioc.ResolveShared<MyStructA>("A");
	px->Fun();
	ioc.RegisterType<MyStructA, Y, int>("B"); // 这里是注册函数类型，不需要带实参
	auto py = ioc.ResolveShared<MyStructA, int>("B", 25); // 这里需要创建对象，需要带实参
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