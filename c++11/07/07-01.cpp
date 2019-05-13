#include "07-01.h"
#include <iostream>
#include <string>

// 7.1 ί�й��캯���ͼ̳й��캯��

// 7.1.1 ί�й��캯��
// ע1��ί�й��캯�����ܲ�����
// ע2��ʹ��ί�й��캯���Ͳ����������Ա��ʼ��
class class_c {
public:
	int max;
	int min;
	int middle;

	class_c(int my_max) { max = my_max > 0 ? my_max : 10; }
	// ί��class_c(my_max)����max�����ڹ��캯�����ڶ���ǹ��첿�֡�
	class_c(int my_max, int my_min) :class_c(my_max) { min = my_min > 0 && my_min < max ? my_min : 1; }
	class_c(int my_max, int my_min, int my_middle) : class_c(my_max, my_min) {
		middle = my_middle < max && my_middle > min ? my_middle : 5;
	}
	//// ί�й��캯�����ܾ���������Ա��ʼ�����ʽ������ʽ�е�, middle(my_middle)��ֻ��ͨ����Ա��ֵ����ʼ��
	//class_c(int my_max, int my_min, int my_middle) : class_c(my_max, my_min), middle(my_middle) {}
};
void test07_01_01() {
	class_c c1(1, 3, 2);
}

// 7.1.2 ���ɹ��캯��
struct Base07 {
	int x;
	double y;
	std::string s;
	Base07(int i) : x(i), y(0) {}
	Base07(int i, double j) : x(i), y(j) {}
	Base07(int i, double j, const std::string& str) :x(i), y(j), s(str) {}
	void func() { std::cout << "call in Base" << std::endl; }
};
// C++����������ػ����ͬ������
// ����������ػ��๹�캯��
struct Derived07_01 : Base07 {
	void func(int a) { std::cout << "call in Derived " << a << std::endl; }
};
// �����������������¶���ͻ�����ͬ�Ĺ��캯��
struct Derived07_02 :Base07 {
	Derived07_02(int i) : Base07(i) {}
	Derived07_02(int i, double j) : Base07(i, j) {};
	Derived07_02(int i, double j, const std::string& str) : Base07(i, j, str) {}
	void func(int a) { std::cout << "call in Derived " << a << std::endl; }
};
// ʹ�ü̳й��캯�����Կ��Խ�����������ػ���ͬ�����캯������
struct Derived07_03 : Base07 {
	using Base07::Base07; // ʹ�û���Ĺ��캯�������̳й��캯��
	// ������ͬ�������������func����
	//void func(int a) { std::cout << "call in Derived " << a << std::endl; }
};
// ��������ʹ�û���ͬ���ĺ���
struct Derived07_04 : Base07 {
	using Base07::Base07; // ʹ�û���Ĺ��캯�������̳й��캯��
	using Base07::func; // ʹ�û����ͬ������
	void func(int a) { std::cout << "call in Derived " << a << std::endl; }
};
void test07_01_02() {
	//Derived07_01 d(1, 2.5, "ok");  // �������û�к��ʵĹ��캯��
	int i = 1;
	double j = 1.23;

	// �����ඨ���Լ��Ĺ��캯��
	Derived07_02 d21(i);
	Derived07_02 d22(i, j);
	Derived07_02 d23(i, j, "");
	//d21.func(); // �����า�ǻ����ͬ������
	d21.func(5);

	// ������ʹ�ü̳й��캯��
	Derived07_03 d31(i);
	Derived07_03 d32(i, j);
	Derived07_03 d33(i, j, "");
	d31.func();

	Derived07_04 d41(i);
	Derived07_04 d42(i, j);
	Derived07_04 d43(i, j, "");
	d41.func();
	d41.func(41);
}

// 7.2 ԭʼ������
// ԭʼ�������Ķ�����R"xxx(raw string)xxx)"����ԭʼ������������()��������
// ����ǰ����Լ�������ͬ���ַ��������ӵ��ַ����ᱻ���ԣ������ַ�����������������ͬʱ����
void test07_02_01() {
	//std::string str1 = R"test(D:\A\B\test.txt)"; // ����testû�г��������ź���
	//std::string str2 = R"test(D:\A\B\test.txt)testaa"; // �����������ߵ��ַ�����ƥ��
	std::string str3 = R"test(D:\A\B\test.txt)test";
	std::string str4 = R"(D:\A\B\test.txt)";
	std::cout << str3 << std::endl;
	std::cout << str4 << std::endl;
}

// 7.3 final��override�ؼ���
struct A7 {
	// A7::foo is final,�޶����麯�����ܱ���д
	virtual void foo() final {};
	//// Error: non-virtual function cannot be final,ֻ�������麯��
	//void bar() final {};
};
struct B7 final : A7 {
	//// error: foo cannot be overrideen as it's final in A7
	//void foo() {}
};
//struct C7 : B7 // Error: B7 is final
//{};
struct A7_2 {
	virtual void func() {}
};
struct D : A7_2 {
	// ��ʾ��д
	void func() override {};
};

// 7.4 �ڴ����
// 7.4.1 �ڴ����
struct MyStruct1 {
	char a;
	int b;
	short c;
	long long d;
	char e;
}; // sizeof(MyStruct1) == 32
struct MyStruct2 {
	char a;
	char e;
	short c;
	int b;
	long long d;
}; // sizeof(MyStruct2) == 16
struct MyStruct3 {
	int b;
	char a;
	short c;
	long long d;
	char e;
};  // sizeof(MyStruct3) == 24
struct MyStruct4 {
	int b;
	char a;
	char f;
	short c;
	long long d;
	char e;
};  // sizeof(MyStruct4) == 24
void test07_04_01() {
	std::cout << sizeof(MyStruct1) << std::endl;
	std::cout << sizeof(MyStruct2) << std::endl;
	std::cout << sizeof(MyStruct3) << std::endl;
	std::cout << sizeof(MyStruct4) << std::endl;
}

// 7.4.2 ���ڴ���ڴ����
// mallocһ��ʹ�õ�ǰƽ̨Ĭ�ϵ���������������ڴ棻���磺MSVC��32λ��һ��8�ֽڶ��룻��64λ������16�ֽڶ���
// ��������Ҫ����һ������ض��ڴ������ڴ��ʱ����MSVC��Ӧ��ʹ��_aligned_malloc,��gcc��һ��ʹ��memalign��
// ������һ������aligned_mallocʵ��
#include <cassert>
inline void* aligned_malloc(size_t size, size_t alignment) {
	// ���alignment�Ƿ���2^N
	assert(!(alignment & (alignment - 1)));
	// �����һ������offset, sizeof(void*)��Ϊ�˴洢ԭʼָ���ַ
	size_t offset = sizeof(void*) + (--alignment);

	// ����һ���offset���ڴ�
	char* p = static_cast<char*>(malloc(offset + size));
	if (!p) return nullptr;

	// ͨ����&(~alignment)���Ѷ�����offset����
	void* r = reinterpret_cast<void*>(reinterpret_cast<size_t>(p + offset) & (~alignment));
	// ��r����һ��ָ��void*��ָ�룬��r��ǰ��ַǰ�����ԭʼ��ַ
	static_cast<void**>(r)[-1] = p;
	// ���ؾ���������ڴ��ַ
	return r;
}
inline void aligned_free(void *p) {
	// ��ԭ��ԭʼ��ַ����free
	free(static_cast<void**>(p)[-1]);
}

// 7.4.3 ����alignasָ���ڴ��С
// alignas����ָ���ڴ����Ĵ�С
alignas(32) long long a = 0;
#define XX 1
struct alignas(XX) MyStruct5 {};
template <size_t YY = 1>
struct alignas(YY) MyStruct6 {};

static const unsigned ZZ = 1;
struct alignas(ZZ) MyStruct7 {};

// alignasֻ�ܸĴ��ܸ�С�������Ҫ��С����Ҫ��#pragma pack����C++11�е�_Pragma
struct MyStruct8 {
	char a;
	alignas(16) int b;
	short c;
	long long d;
	char e;
};

void test07_04_03() {
	std::cout << sizeof(MyStruct5) << std::endl;
	std::cout << sizeof(MyStruct6<4>) << std::endl;
	std::cout << sizeof(MyStruct7) << std::endl;
	std::cout << sizeof(MyStruct8) << std::endl;
}

// 7.4.4 ����alignof��std::alignment_of��ȡ�ڴ�����С
struct MyStruct9 {
	char a;
	int b;
	double c;
};
void test07_04_04() {
	MyStruct9 xx;
	//std::cout << alignof(xx) << std::endl; // error C2061: �﷨����: ��ʶ����xx��
	std::cout << alignof(MyStruct9) << std::endl;
	std::cout << std::alignment_of<MyStruct9>::value << std::endl;
}

// 7.4.5 �ڴ���������std::aligned_storage
struct A745 {
	int avg;
	A745(int a, int b) : avg((a + b) / 2) {}
};
void test07_04_05() {
	typedef std::aligned_storage<sizeof(A745), alignof(A745)>::type Aligned_A745;
	Aligned_A745 a, b;
	new (&a) A745(10, 20); // placement new
	b = a;
	std::cout << reinterpret_cast<A745&>(b).avg << std::endl;

	char xx[32];
	::new (xx) MyStruct9; // placement new

	std::aligned_storage<sizeof(MyStruct9), alignof(MyStruct9)>::type yy;
	::new (&yy) MyStruct9;
}

struct alignas(32) MyStruct10 {
	char a;
	int b;
	short c;
	long long d;
	char e;
};
void test07_04_06() {
	void* p = new MyStruct10; // warning C4316: ��MyStruct10��: �ڶ��Ϸ���Ķ�����ܲ��Ƕ��� 32
}

// 7.4.6 std::max_align_t��std::align������
#include <memory>
void test07_04_07() {
	// std::max_align_t�������ص�ǰƽ̨�����Ĭ���ڴ�������͡�
	// ����malloc���ص��ڴ棬������max_align_t���͵Ķ����СӦ��һ�¡�
	std::cout << alignof(std::max_align_t) << std::endl;
	char buffer[] = "-----------------";
	void* pt = buffer;
	std::size_t space = sizeof(buffer) - 1;
	std::align(alignof(int), sizeof(char), pt, space);
	// ��buffer������ڴ���У�ָ���ڴ����Ϊalignof(int)����һ��sizeof(char)��С���ڴ棬
	// �������ҵ�����ڴ�󽫵�ַ����pt����buffer��pt��ʼ�ĳ��ȷ���space��
}

// 7.5 C++11�����ı����㷨
// 7.5.1 all_of,any_of��none_of�㷨
#include <iostream>
#include <algorithm>
#include <vector>
void test07_05_01() {
	std::vector<int> v = { 1, 3, 5, 7, 9 };
	auto isEven = [](int i) { return i % 2 != 0; };
	bool isAllOdd = std::all_of(v.begin(), v.end(), isEven);
	if (isAllOdd) {
		std::cout << "all is odd" << std::endl;
	}
	bool isNoneEven = std::none_of(v.begin(), v.end(), isEven);
	if (isNoneEven) {
		std::cout << "none is even" << std::endl;
	}
	std::vector<int> v1 = { 1, 3, 5, 7, 8, 9 };
	bool anyof = std::any_of(v1.begin(), v1.end(), isEven);
	if (anyof) {
		std::cout << "at least one is even" << std::endl;
	}
}
// 7.5.2 find_if_not
void test07_05_02() {
	std::vector<int> v = { 1, 3, 5, 7, 9, 4 };
	auto isEven = [](int i) {return i % 2 == 0; };
	auto firstEven = std::find_if(v.begin(), v.end(), isEven);
	if (firstEven != v.end()) {
		std::cout << "the first even is " << *firstEven << std::endl;
	}

	// ��find_if������������Ҫ����дһ���񶨺�����ж�ʽ
	auto isNotEven = [](int i) {return i % 2 != 0; };
	auto firstOdd = std::find_if(v.begin(), v.end(), isNotEven);
	if (firstOdd != v.end()) {
		std::cout << "the first odd is " << *firstOdd << std::endl;
	}

	// ��find_if_not�����������趨�����ж�ʽ
	auto odd = std::find_if_not(v.begin(), v.end(), isEven);
	if (odd != v.end()) {
		std::cout << "the first odd is " << *odd << std::endl;
	}
}

// 7.5.3 copy_if
void test07_05_03() {
	std::vector<int> v = { 1, 3, 5, 7, 9, 4 };
	std::vector<int> v1(v.size());
	// ������������
	auto it = std::copy_if(v.begin(), v.end(), v1.begin(), [](int i) {return i % 2 == 0; });
	// ��Сvector�����ʴ�С
	v1.resize(std::distance(v1.begin(), it));
	for (int& i : v1) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

// 7.5.4 iota
#include <numeric>
#include <array>
void test07_05_04() {
	std::vector<int>v(4);
	// ֱ��ͨ��iota��ʼ������
	std::iota(v.begin(), v.end(), 1);
	for (auto& n : v) {
		std::cout << n << " ";
	}
	std::cout << std::endl;

	std::array<int, 4> a;
	std::iota(a.begin(), a.end(), 1);
	for (auto& n : a) {
		std::cout << n << " ";
	}
	std::cout << std::endl;
}

// 7.5.5 minmax_element
void test07_05_05() {
	std::vector<int> v = { 1, 2, 5, 7, 9, 4 };
	auto result = minmax_element(v.begin(), v.end());
	std::cout << *result.first << " " << *result.second << std::endl;
}

// 7.5.6 is_sorted��is_sorted_until
void test07_05_06() {
	std::vector<int> v = { 1, 2, 5, 7, 9, 4 };
	auto pos = is_sorted_until(v.begin(), v.end());
	for (auto it = v.begin(); it != v.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	bool is_sort = std::is_sorted(v.begin(), v.end());
	std::cout << is_sort << std::endl;
}
void test07() {
	test07_01_01();
	test07_01_02();
	test07_02_01();
	test07_04_01();
	test07_04_03();
	test07_04_04();
	test07_04_05();
	test07_04_06();
	test07_04_07();
	test07_05_01();
	test07_05_02();
	test07_05_03();
	test07_05_04();
	test07_05_05();
	test07_05_06();
	return;
}
