#include "04-01.h"
#include <iostream>
#include <memory>
#include <functional>

// ���ϣ��ֻ��һ������ָ�������Դ���߹����������unique_ptr
// ���ϣ���������ָ�����ͬһ����Դ����shared_ptr
// ������weak_ptr����������shared_ptr��,weak_ptr�������������1��
// weak_ptr������shared_ptr���ڲ�ָ��,��ҪΪ�˼���shared_ptr����������,������shared_ptr��һ�����֡�

// 4.1 shared_ptr ���������ָ��
// 4.1.1 shared_ptr�Ļ����÷�

// ����ָ��ɾ����
void DeleteIntPtr(int* p) {
	delete p;
}

// ��װmake_shared_array������shared_ptr֧������
template<typename T>
std::shared_ptr<T> make_shared_array(size_t size) {
	return std::shared_ptr<T>(new T[size], std::default_delete<T[]>());
}

void test_04_1_1() {
    // 1. ����ָ��ĳ�ʼ��
	std::shared_ptr<int> p(new int(1));
	std::shared_ptr<int> p2 = p;
	std::shared_ptr<int> ptr;
	ptr.reset(new int(1));
	if (ptr) {
		std::cout << "ptr is not null" << std::endl;
	}
	// ע��01��������ԭʼָ��Ϊ����ָ�븳ֵ
	// ������󣬲�����ֱ�Ӹ�ֵ;
	// error C2440: ����ʼ����: �޷��ӡ�int *��ת��Ϊ��std::shared_ptr<int>��
	//std::shared_ptr<int> err_p = new int(1);

	// 2 ��ȡԭʼָ��
	int * original_pointer = p.get();
	std::cout << *original_pointer << std::endl;

	// 3 ָ��ɾ����
	std::shared_ptr<int> p3(new int(3), DeleteIntPtr);
	std::shared_ptr<int> p4(new int(3), [](int* p) {delete p; });

	// a.ʹ��shared_ptr����̬����ʱ����Ҫָ��ɾ����,std::shared_ptrĬ��ɾ������֧���������
	std::shared_ptr<int> p5(new int[10], [](int* p) {delete[] p; }); // ָ��delete[]

	// b.std::default_delete��shared_ptr��Ĭ��ɾ����
	std::shared_ptr<int> p6(new int[10], std::default_delete<int[]>());

	// c.��װ�Ӽ�������������
	std::shared_ptr<int> p7 = make_shared_array<int>(10);
	std::shared_ptr<char> p8 = make_shared_array<char>(10);
}

// ��������shared_ptr�ĺ���
void test_func() {

}
void func04_1_2(std::shared_ptr<int> sp1, void(*funcxxx)()) {
	if (funcxxx) {
		funcxxx();
	}
}
struct A04_1_2A {
	std::shared_ptr<A04_1_2A> GetSelf() {
		// �������ᵼ���ظ�����
		return std::shared_ptr<A04_1_2A>(this); // don't do this!
	}
};
struct A04_1_2B : public std::enable_shared_from_this<A04_1_2B> {
	std::shared_ptr<A04_1_2B> GetSelf() {
		// ʹ��shared_from_this()����this��shared_ptr
		return shared_from_this();
	}
};
// shared_ptrѭ������
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

// ʹ��shared_ptr��Ҫע�������
void error_04_1_2() {
	// a ������һ��ԭʼָ���ʼ�����shared_ptr
	int* ptr = new int(2);
	std::shared_ptr<int> p1(ptr);
	//std::shared_ptr<int> p2(ptr); // logic error
	//// ����ʱ����p2�ڳ�������ʱ���ٴ��ͷ�ptrָ��

	// b �����ں���ʵ���д���shared_ptr,���ܷ�������
	func04_1_2(std::shared_ptr<int>(new int(4)), test_func); // δ�س���,��ȱ��
	// Ӧ����ʵ�����洴��shared_ptr
	std::shared_ptr<int> sp2(new int(5));
	func04_1_2(sp2, test_func);  // ok

	//// c Ҫͬ��shared_from_this()����thisָ�롣���ܽ�thisָ����Ϊshared_ptr���س�����
	//// ��Ϊthisָ�뱾������һ����ָ�룬�������ᵼ���ظ�������
	//std::shared_ptr<A04_1_2A> sp3(new A04_1_2A);
	//std::shared_ptr<A04_1_2A> sp4 = sp3->GetSelf(); // �ظ�����

	std::shared_ptr<A04_1_2B> sp5(new A04_1_2B);
	std::shared_ptr<A04_1_2B> sp6 = sp5->GetSelf();

	// d ѭ������
	{
		std::shared_ptr<A04_1_2C> cp(new A04_1_2C);
		std::shared_ptr<A04_1_2D> dp(new A04_1_2D);
		cp->dptr = dp;
		dp->cptr = cp;
		// �����������dp��cp��δ�ͷţ���������δ������
	}
}

// unique_ptr��ռ������ָ��
void test_04_2_1() {
	std::unique_ptr<int> myPtr(new int);
	//std::unique_ptr<int> myPtr2 = myPtr; // ���󣬲�������(error C2280)
	std::unique_ptr<int> myPtr3 = std::move(myPtr); // ����ͨ��std::move��ת��������std::unique_ptr
}

// �Զ���make_unique,C++14���Ѿ������make_unique
// ֧����ָͨ��
template<class T, class... Args> inline
typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
make_unique(Args&& ...args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
// ֧�ֶ�̬����
template<class T> inline
typename std::enable_if<std::is_array<T>::value && std::extent<T>::value == 0, std::unique_ptr<T>>::type
make_unique(size_t size) {
	typedef typename std::remove_extent<T>::type U;
	return std::unique_ptr<T>(new U[size]());
}
// ���˶�����������
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
// �Զ���ɾ����
struct MyDeleter {
	void operator() (int *p) {
		std::cout << "MyDeleter --> delete" << std::endl;
		delete p;
	}
};
void test_04_2_3() {
	// unique_ptr����ָ��һ������
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

	//std::shared_ptr<int[]> ptr2(new int[10]); // ����error C2664: �޷������� 1 �ӡ�int *��ת��Ϊ��int (*)[]��

	// unique_ptr��shared_ptr��ɾ����������ͬ
	// unique_ptr��ɾ������Ҫȷ��ɾ����������
	// lambda���ʽ��û�в������ʱ������ת��Ϊ����ָ��
	std::shared_ptr<int> ptr2(new int(1), [](int *p) {delete p; });
	//std::unique_ptr<int> ptr3(new int(1), [](int* p) {delete p; }); // ����
	std::unique_ptr<int, void(*)(int*)> ptr4(new int(1), [](int* p) {delete p; });
	//// �������lambda���ʽ�����˱��������б��뱨��
	//// lambda���ʽ��������󣬲���ת��Ϊ����ָ��
	//std::unique_ptr<int, void(*)(int*)> ptr5(new int(1), [&](int* p) {delete p; });

	// ϣ��unique_ptr֧��ɾ��������Ҫ�ú�����װ��
	std::unique_ptr<int, std::function<void(int*)>> ptr6(new int(1), [&](int* p) {delete p; });

	// ʹ���Զ���ɾ����
	std::unique_ptr<int, MyDeleter> p(new int(1));
}

// 4.3 weak_ptr�����õ�����ָ��
// 4.3.1 weak_ptr�����÷�
void test_04_3_1() {
	// ͨ��use_count()��������õ�ǰ�۲���Դ�����ü���
	std::shared_ptr<int> sp(new int(10));
	std::weak_ptr<int> wp(sp);
	std::cout << wp.use_count() << std::endl;

	// ͨ��expired()�������ж����۲�����Ƿ��Ѿ����ͷ�
	if (wp.expired()) {
		std::cout << "weak_ptr��Ч,�����ӵ���Դ�ѱ��ͷ�!" << std::endl;
	}
	else {
		std::cout << "weak_ptr��Ч" << std::endl;
	}

	// ͨ��lock()����ȡ�����ӵ�shared_ptr
	if (!wp.expired()) {
		auto spt = wp.lock();
		std::cout << "shared_ptr��ָ��Դ:" << *spt << std::endl;
	}
}

// 4.3.2 weak_ptr����thisָ��
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

// 4.3.3 ���ѭ����������
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

// 4.4 ͨ������ָ�����������������ڴ�
// void* p = GetHandle()->Create(); // �������������ڴ棬���Դ�������new����
// GetHandle()->Release(p); // ���Դ�����delete����
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
		// do something... ��ò���ȫ
	}
}

#define GUARD(p) std::shared_ptr<void> p##p(p, [](void* p) {delete p; /* GetHandle()->Release(p); */});
void test_04_4_3() {
	void* p = new char('b'); // GetHandle()->Create();
	GUARD(p); // ��ȫ
}
// Ҳ����unique_ptr��������������ڴ�
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