#include "04-01.h"
#include <iostream>
#include <memory>
#include <functional>

// 如果希望只有一个智能指针管理资源或者管理数组就用unique_ptr
// 如果希望多个智能指针管理同一个资源就用shared_ptr
// 弱引用weak_ptr是用来监视shared_ptr的,weak_ptr不会引起计数加1，
// weak_ptr不管理shared_ptr的内部指针,主要为了监视shared_ptr的生命周期,更像是shared_ptr的一个助手。

// 4.1 shared_ptr 共享的智能指针
// 4.1.1 shared_ptr的基本用法

// 智能指针删除器
void DeleteIntPtr(int* p) {
	delete p;
}

// 封装make_shared_array方法让shared_ptr支持数组
template<typename T>
std::shared_ptr<T> make_shared_array(size_t size) {
	return std::shared_ptr<T>(new T[size], std::default_delete<T[]>());
}

void test_04_1_1() {
    // 1. 智能指针的初始化
	std::shared_ptr<int> p(new int(1));
	std::shared_ptr<int> p2 = p;
	std::shared_ptr<int> ptr;
	ptr.reset(new int(1));
	if (ptr) {
		std::cout << "ptr is not null" << std::endl;
	}
	// 注意01：不能用原始指针为智能指针赋值
	// 编译错误，不允许直接赋值;
	// error C2440: “初始化”: 无法从“int *”转换为“std::shared_ptr<int>”
	//std::shared_ptr<int> err_p = new int(1);

	// 2 获取原始指针
	int * original_pointer = p.get();
	std::cout << *original_pointer << std::endl;

	// 3 指定删除器
	std::shared_ptr<int> p3(new int(3), DeleteIntPtr);
	std::shared_ptr<int> p4(new int(3), [](int* p) {delete p; });

	// a.使用shared_ptr管理动态数组时，需要指定删除器,std::shared_ptr默认删除器不支持数组对象
	std::shared_ptr<int> p5(new int[10], [](int* p) {delete[] p; }); // 指定delete[]

	// b.std::default_delete是shared_ptr的默认删除器
	std::shared_ptr<int> p6(new int[10], std::default_delete<int[]>());

	// c.封装子集的数组生成器
	std::shared_ptr<int> p7 = make_shared_array<int>(10);
	std::shared_ptr<char> p8 = make_shared_array<char>(10);
}

// 参数中有shared_ptr的函数
void test_func() {

}
void func04_1_2(std::shared_ptr<int> sp1, void(*funcxxx)()) {
	if (funcxxx) {
		funcxxx();
	}
}
struct A04_1_2A {
	std::shared_ptr<A04_1_2A> GetSelf() {
		// 这样做会导致重复析构
		return std::shared_ptr<A04_1_2A>(this); // don't do this!
	}
};
struct A04_1_2B : public std::enable_shared_from_this<A04_1_2B> {
	std::shared_ptr<A04_1_2B> GetSelf() {
		// 使用shared_from_this()返回this给shared_ptr
		return shared_from_this();
	}
};
// shared_ptr循环引用
struct A04_1_2C;
struct A04_1_2D;
struct A04_1_2C {
	std::shared_ptr<A04_1_2D> dptr;
	~A04_1_2C() {
		std::cout << "A04_1_2C is deleted!" << std::endl;
	}
};
struct A04_1_2D {
	std::shared_ptr<A04_1_2C> cptr;
	~A04_1_2D() {
		std::cout << "A04_1_2D is deleted!" << std::endl;
	}
};

// 使用shared_ptr需要注意的问题
void error_04_1_2() {
	// a 不能用一个原始指针初始化多个shared_ptr
	int* ptr = new int(2);
	std::shared_ptr<int> p1(ptr);
	//std::shared_ptr<int> p2(ptr); // logic error
	//// 运行时错误，p2在出作用域时，再次释放ptr指针

	// b 不能在函数实参中创建shared_ptr,可能发生错误
	func04_1_2(std::shared_ptr<int>(new int(4)), test_func); // 未必出错,有缺陷
	// 应该在实参外面创建shared_ptr
	std::shared_ptr<int> sp2(new int(5));
	func04_1_2(sp2, test_func);  // ok

	//// c 要同构shared_from_this()返回this指针。不能将this指针作为shared_ptr返回出来，
	//// 因为this指针本质上是一个裸指针，这样做会导致重复析构。
	//std::shared_ptr<A04_1_2A> sp3(new A04_1_2A);
	//std::shared_ptr<A04_1_2A> sp4 = sp3->GetSelf(); // 重复析构

	std::shared_ptr<A04_1_2B> sp5(new A04_1_2B);
	std::shared_ptr<A04_1_2B> sp6 = sp5->GetSelf();

	// d 循环引用
	{
		std::shared_ptr<A04_1_2C> cp(new A04_1_2C);
		std::shared_ptr<A04_1_2D> dp(new A04_1_2D);
		cp->dptr = dp;
		dp->cptr = cp;
		// 出了作用域后，dp，cp均未释放，析构函数未被调用
	}
}

// unique_ptr独占的智能指针
void test_04_2_1() {
	std::unique_ptr<int> myPtr(new int);
	//std::unique_ptr<int> myPtr2 = myPtr; // 错误，不允许复制(error C2280)
	std::unique_ptr<int> myPtr3 = std::move(myPtr); // 允许通过std::move来转移其它的std::unique_ptr
}

// 自定义make_unique,C++14中已经提高了make_unique
// 支持普通指针
template<class T, class... Args> inline
typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
make_unique(Args&& ...args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
// 支持动态数组
template<class T> inline
typename std::enable_if<std::is_array<T>::value && std::extent<T>::value == 0, std::unique_ptr<T>>::type
make_unique(size_t size) {
	typedef typename std::remove_extent<T>::type U;
	return std::unique_ptr<T>(new U[size]());
}
// 过滤定长数组的情况
template <class T, class... Args>
typename std::enable_if<std::extent<T>::value != 0, void>::type make_unique(Args ...args) = delete;

void test_04_2_2() {
	auto unique = make_unique<int>(100);
	std::cout << *unique << std::endl;

	auto unique2 = make_unique<int[]>(10);
	for (int i = 0; i < 10; i++)
	{
		unique2[i] = i;
	}
	for (int i = 0; i < 10; i++)
	{
		std::cout << unique2[i] << " ";
	}
	std::cout << std::endl;
}
// 自定义删除器
struct MyDeleter {
	void operator() (int *p) {
		std::cout << "MyDeleter --> delete" << std::endl;
		delete p;
	}
};
void test_04_2_3() {
	// unique_ptr可以指向一个数组
	std::unique_ptr<int[]> ptr(new int[10]{1, 2, 3, 4, 5, 6});
	std::cout << "test_04_2_3()" << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << ptr[i] << " ";
		ptr[i] = i * 10;
	}
	std::cout << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << ptr[i] << " ";
	}
	std::cout << std::endl;

	//std::shared_ptr<int[]> ptr2(new int[10]); // 错误error C2664: 无法将参数 1 从“int *”转换为“int (*)[]”

	// unique_ptr和shared_ptr的删除器方法不同
	// unique_ptr的删除器需要确定删除器的类型
	// lambda表达式在没有捕获变量时，可以转换为函数指针
	std::shared_ptr<int> ptr2(new int(1), [](int *p) {delete p; });
	//std::unique_ptr<int> ptr3(new int(1), [](int* p) {delete p; }); // 错误
	std::unique_ptr<int, void(*)(int*)> ptr4(new int(1), [](int* p) {delete p; });
	//// 如果上述lambda表达式捕获了变量，会有编译报错
	//// lambda表达式捕获变量后，不能转换为函数指针
	//std::unique_ptr<int, void(*)(int*)> ptr5(new int(1), [&](int* p) {delete p; });

	// 希望unique_ptr支持删除器，需要用函数包装器
	std::unique_ptr<int, std::function<void(int*)>> ptr6(new int(1), [&](int* p) {delete p; });

	// 使用自定义删除器
	std::unique_ptr<int, MyDeleter> p(new int(1));
}

// 4.3 weak_ptr弱引用的智能指针
// 4.3.1 weak_ptr基本用法
void test_04_3_1() {
	// 通过use_count()方法来获得当前观测资源的引用计数
	std::shared_ptr<int> sp(new int(10));
	std::weak_ptr<int> wp(sp);
	std::cout << wp.use_count() << std::endl;

	// 通过expired()方法来判定所观测的资是否已经被释放
	if (wp.expired()) {
		std::cout << "weak_ptr无效,所监视的资源已被释放!" << std::endl;
	}
	else {
		std::cout << "weak_ptr有效" << std::endl;
	}

	// 通过lock()来获取所监视的shared_ptr
	if (!wp.expired()) {
		auto spt = wp.lock();
		std::cout << "shared_ptr所指资源:" << *spt << std::endl;
	}
}

// 4.3.2 weak_ptr返回this指针
struct A04_3_2_0 : public std::enable_shared_from_this<A04_3_2_0> {
	std::shared_ptr<A04_3_2_0> GetSelf() {
		return shared_from_this();
	}
	~A04_3_2_0() {
		std::cout << "A04_3_2_0 is deleted" << std::endl;
	}
};
void test_04_3_2() {
	std::shared_ptr<A04_3_2_0> spy(new A04_3_2_0);
	std::shared_ptr<A04_3_2_0> p = spy->GetSelf();
}

// 4.3.3 解决循环引用问题
struct A04_3_3_A;
struct A04_3_3_B;
struct A04_3_3_A {
	std::shared_ptr<A04_3_3_B> bptr;
	~A04_3_3_A() { std::cout << "A04_3_3_A is deleted!" << std::endl; }
};
struct A04_3_3_B {
	std::weak_ptr<A04_3_3_A> aptr;
	~A04_3_3_B() { std::cout << "A04_3_3_B is deleted!" << std::endl; }
};
void test_04_3_3() {
	{
		std::shared_ptr<A04_3_3_A> ap(new A04_3_3_A);
		std::shared_ptr<A04_3_3_B> bp(new A04_3_3_B);
		ap->bptr = bp;
		bp->aptr = ap;
	}
}

// 4.4 通过智能指针管理第三方库分配的内存
// void* p = GetHandle()->Create(); // 第三方库分配的内存，测试代码中用new代替
// GetHandle()->Release(p); // 测试代码用delete代替
void test_04_4_1() {
	void* p = new char[100]; // GetHandle()->Create();
	std::shared_ptr<void> sp(p, [&/*this*/](void* p) {delete[] p; /* GetHandle()->Release(p); */});
}

std::shared_ptr<void> Guard(void *p) {
	if (nullptr == p) {
		return nullptr;
	}
	std::shared_ptr<void> sp(p, [&/*this*/](void* p) {delete p; /* GetHandle()->Release(p); */});
	return sp;
}
void test_04_4_2() {
	{
		void* p = new char('a'); // GetHandle()->Create();
		auto sp = Guard(p);
	}
	{
		void* p = new char('a'); // GetHandle()->Create();
		Guard(p);
		// do something... 变得不安全
	}
}

#define GUARD(p) std::shared_ptr<void> p##p(p, [](void* p) {delete p; /* GetHandle()->Release(p); */});
void test_04_4_3() {
	void* p = new char('b'); // GetHandle()->Create();
	GUARD(p); // 安全
}
// 也可用unique_ptr来管理第三方的内存
#define GUARD2(p) std::unique_ptr<void, void(*)(void*)> p##p(p, [](void* p) {delete p; /*GetHandle()->Release(p);*/});
void test_04_4_4() {
	void* p = new double(4.44);
	GUARD2(p);
}

void test04() {
	test_04_1_1();
	error_04_1_2();
	test_04_2_1();
	test_04_2_2();
	test_04_2_3();
	test_04_3_1();
	test_04_3_2();
	test_04_3_3();
	test_04_4_1();
	test_04_4_2();
	test_04_4_3();
	test_04_4_4();
	return;
}