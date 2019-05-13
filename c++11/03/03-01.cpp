#include "03-01.h"
#include <type_traits>
#include <memory>
#include <string>
#include <functional>
#include <iostream>

// 3.1 type_traits--类型萃取
// type_traits提供了丰富的编译期计算、查询、判断、转换和选择的帮助类。
// type_traits可以大大降低程序的圈复杂度
// 3.1.1 基本的type_traits
// 1.简单的type_traits

// 定义一个编译期常量

// C++11之前的写法
template <typename Type>
struct GetLeftSize1 {
	static const int value = 1;
};
// GetLeftSize1<int>::value

// 采用enum来定义编译期常量
template <typename Type>
struct GetLeftSize2 {
	enum { value = 1 };
};
// GetLeftSize2<int>::value

// C++11中的写法
template <typename Type>
struct GetLeftSize3 :std::integral_constant <int, 1>
{
};
// GetLeftSize3<int>::value

// 编译期常量的定义方式
// C++11中integral_constant定义
template <class T, T v>
struct integral_constant {
	static constexpr T value = v;
	typedef T value_type;
	typedef integral_constant<T, v> type;
	operator value_type() { return value; }
};
typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

// C++定义一个常量字符串的方式
using my_03_01_type_5 = std::integral_constant<int,5>;
using my_03_03type_char_a = std::integral_constant<char, 'a'>;
//using my_03_03type_str = std::integral_constant<std::string, "">; // 原始类型可以，类似于std::string类型不可

void test03_01_01(void)
{
	std::cout << "编译期静态常量static " << GetLeftSize1<int>::value << std::endl;
	std::cout << "编译期静态常量enum " << GetLeftSize2<int>::value << std::endl;
	std::cout << "编译期静态常量C++11 " << GetLeftSize3<int>::value << std::endl;

	std::cout << "true_type::value: " << true_type::value << std::endl;
	std::cout << "false_type::value: " << false_type::value << std::endl;

	return;
}

// 2 类型判断的type_traits
//template<class T> struct is_void;           // T是否为void类型
//template<class T> struct is_floting_point;  // T是否为浮点类型
//template<class T> struct is_array;          // T是否为数组类型
//template<class T> struct is_pointer;        // T是否为指针类型(包括函数指针，但不包含成员(函数)指针)
//template<class T> struct is_enum;           // T是否为枚举类型
//template<class T> struct is_union;          // T是否为union的class/struct
//template<class T> struct is_class;          // T是否为类类型而不是union类型
//template<class T> struct is_function;       // T是否为函数类型
//template<class T> struct is_reference;      // T是否为引用类型(左值引用或右值引用)
//template<class T> struct is_arithmetic;     // T是否为整型或浮点类型
//template<class T> struct is_fundamental;    // T是否为整型、浮点、void或nullptr_t类型
//template<class T> struct is_object;         // T是否为一个对象类型(不是函数、不是引用、不是void)
//template<class T> struct is_scalar;         // T是否为arithmetic、enumeration、pointer、pointer to number或std::nullptr_t类型
//template<class T> struct is_compound;       // T是否为非fundamental类型构造的
//template<class T> struct is_member_pointer; // T是否为成员函数指针类型
//template<class T> struct is_polymorphic;    // T是否为虚函数
//template<class T> struct is_abstract;       // T是否为抽象类
//template<class T> struct is_signed;         // T是否为有符号类型
//template<class T> struct is_unsigned;       // T是否为无符号类型
//template<class T> struct is_const;          // T是否为const修饰的类型
void test03_01_02() {
	std::cout << "is_const" << std::endl;
	std::cout << "int: " << std::is_const<int>::value << std::endl;
	std::cout << "const int: " << std::is_const<const int>::value << std::endl;
	std::cout << "const int&: " << std::is_const<const int&>::value << std::endl;
	std::cout << "const int*: " << std::is_const<const int*>::value << std::endl;
	std::cout << "int*: " << std::is_const<int*>::value << std::endl;
	/* vs2017
	is_const
	int: 0
	const int: 1
	const int&: 0
	const int*: 0
	int*: 0 */
}

// 3 判断两个类型之间的关系
//template <class T, class U> struct is_same; // 判断两个类型是否相同
//template <class Base, class Derived> struct is_base_of; // 判断Base类型是否为Derived类型的基类
//template <class From, class To> struct is_convertible; // 判断From类型是否能转换为To类型
void test03_01_03() {
	// (1) is_same的用法
	std::cout << std::is_same<int, int>::value << std::endl;  // 1
	std::cout << std::is_same<int, unsigned int>::value << std::endl; // 0
	std::cout << std::is_same<int, signed int>::value << std::endl; // 1

	// (2) is_base_of的用法
	class A {};
	class B :public A {};
	class C {};
	std::cout << std::is_base_of<A, B>::value << std::endl; // 1
	std::cout << std::is_base_of<B, A>::value << std::endl; // 0
	std::cout << std::is_base_of<C, B>::value << std::endl; // 0

	// (3) is_convertible的用法
	bool b2a = std::is_convertible<B*, A*>::value;
	bool a2b = std::is_convertible<A*, B*>::value;
	bool b2c = std::is_convertible<B*, C*>::value;
	std::cout << std::boolalpha << b2a << " " << a2b << " " << b2c << std::endl;
	// true false false
}

// 4 类型转换的traits
//template<class T> struct remove_const;          // 移除const
//template<class T> struct add_const;             // 添加const
//template<class T> struct remove_reference;      // 移除引用
//template<class T> struct add_lvalue_reference;  // 添加左值引用
//template<class T> struct add_rvalue_reference;  // 添加右值引用
//template<class T> struct remove_extent;         // 移除数组顶层的维度
//template<class T> struct remove_all_extents;    // 移除数组所有维度
//template<class T> struct remove_pointer;        // 移除指针
//template<class T> struct add_pointer;           // 添加指针
//template<class T> struct decay;                 // 移除cv或添加指针
//template<class T> struct common_type;           // 获取公共资源
void test03_01_04() {
	std::cout << __FUNCTION__ << " start" << std::endl;
	std::cout << std::is_same<const int, std::add_const<int>::type>::value << std::endl;
	std::cout << std::is_same<int, std::remove_const<const int>::type>::value << std::endl;
	std::cout << std::is_same<int&, std::add_lvalue_reference<int>::type>::value << std::endl;
	std::cout << std::is_same<int&&, std::add_rvalue_reference_t<int>>::value << std::endl;
	std::cout << std::is_same<int, std::remove_reference_t<int&>>::value << std::endl;
	std::cout << std::is_same<int, std::remove_reference<int&&>::type>::value << std::endl;
	std::cout << std::is_same<int*, std::add_pointer_t<int>>::value << std::endl;
	std::cout << std::is_same<int, std::remove_extent<int[]>::type>::value << std::endl;
	std::cout << std::is_same<int[2], std::remove_extent<int[][2]>::type>::value << std::endl;
	std::cout << std::is_same<int[2][3], std::remove_extent<int[][2][3]>::type>::value << std::endl;
	std::cout << std::is_same<int, std::remove_all_extents<int[][2][3]>::type>::value << std::endl;
	typedef std::common_type<unsigned char, short, int>::type NumericType;
	std::cout << std::is_same<int, NumericType>::value << std::endl;
	std::cout << __FUNCTION__ << " end" << std::endl;
}
//// 根据模板参数创建对象，需要注意移除指针
//template<typename T>
//typename std::remove_reference<T>::type* Create() {
//	typedef typename std::remove_reference<T>::type U;
//	return new U();
//}
// 移除和添加引用
template <class T>
struct Construct {
	typedef typename std::remove_reference<T>::type U; // 移除可能的引用
	Construct() : m_ptr(new U) { }
	typename std::add_lvalue_reference<T>::type Get() const { // 添加左值引用
		return *m_ptr.get();
	}
private:
	std::unique_ptr<U> m_ptr;
};
void test03_01_05() {
	Construct<int> c;
	int a = c.Get();
	std::cout << a << std::endl;
}

// ====================================================================================
//// 编译不过
//template<typename T>
//T* Create1() {
//	return new T();
//}
//int *p1 = Create1<const volatile int&>();
// 改为
template<typename T>
typename std::remove_cv<typename std::remove_reference<T>::type>::type* Create2() {
	typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type U;
	return new U();
}
int *p2 = Create2<const volatile int&>();
// 或者
template<typename T>
typename std::decay<T>::type* Create3() {
	typedef typename std::decay<T>::type U;
	return U();
}
int *p3 = Create3<const volatile int&>();
//std::decay可以移除引用和cv限定符，还可以用于数组和函数
// std::decay的转换规则
// a 先移除T类型的引用，得到类型U，U定义为remove_reference<T>::type
// b 如果is_array<U>::type未true,修改类型type为remove_extent<U>::type*
// c 否则,如果is_function<U>::value为true,修改类型type为add_pointer<U>::type
// d 否则,修改类型type为remove_cv<U>::type
typedef std::decay<int>::type A; // int
typedef std::decay<int&>::type B; // int
typedef std::decay<int&&>::type C; // int
typedef std::decay<const int&>::type D; //int
typedef std::decay<int[2]>::type E; // int*
typedef std::decay<int(int)>::type F; // int(*)(int)
template<typename F>
struct SimpFunction {
	using FnType = typename std::decay<F>::type;
	SimpFunction(F& f) : m_fn(f) {}
	void Run() {
		m_fn();
	}
	FnType m_fn;
};
// ====================================================================================

// 3.1.2 根据条件选择的traits
//template <bool B, class T, class F> struct conditional;
void test03_01_06() {
	typedef std::conditional<true, int, float>::type A;
	typedef std::conditional<false, int, float>::type B;
	typedef std::conditional<std::is_integral<A>::value, long, int>::type C;
	typedef std::conditional<std::is_integral<B>::value, long, int>::type D;
	std::cout << __FUNCTION__ << ": " << typeid(A).name() << " " << typeid(B).name() 
		<< " " << typeid(C).name() << " " << typeid(D).name() << std::endl;
	typedef std::conditional <(sizeof(long long) > sizeof(long double)), long long, long double > ::type max_size_t;
	std::cout << __FUNCTION__ << ": " << typeid(max_size_t).name() << std::endl;
    //test03_01_06: int float long int
	//test03_01_06 : long double
}

// 3.1.3 获取可调用对象返回类型的traits
//// 获取函数返回值类型比较困难
//template <typename F, typename Arg>
//?? Func(F f, Arg arg) { // 如何确定返回值类型
//	return f(arg);
//}
// 获取函数返回值类型1
double func03_01_07A(int a) { return 2.5 * a; }
template <typename F, typename Arg>
decltype((*(F*)0)((*(Arg*)0))) Func03_01_07A(F f, Arg arg) {
	return f(arg);
}
template <typename F, typename Arg>
auto Func03_01_07B(F f, Arg arg)->decltype(f(arg)) {
	return f(arg);
}
int fn(int a) { return a; };  // function
typedef int(&fn_ref) (int);   // function reference
typedef int(*fn_ptr) (int);   // function pointer
struct fn_class {
	int operator()(int i) { return i; }
}; // function-like class
void test03_01_07() {
	//Func03_01_07A<double(*)(int), int>(func03_01_07A, 5);
	std::cout << __FUNCTION__ << " A: " << Func03_01_07A<double(*)(int), int>(func03_01_07A, 5) << std::endl;
	//Func03_01_07B<double(*)(int), int>(func03_01_07A, 7);
	std::cout << __FUNCTION__ << " B: " << Func03_01_07B<double(*)(int), int>(func03_01_07A, 7) << std::endl;
	class A0 {
		A0() = delete;
	public:
		int operator() (int i) {
			return i;
		}
	};
	//decltype(A0()(0)) i = 4; // A没有默认构造函数，编译报错
	decltype(std::declval<A0>()(std::declval<int>())) x = 4;
	std::cout << x << std::endl;

	//template<class F, class... Args> class result_of<F(Args...)>;
	std::result_of<A0(int)>::type y = 5;
	std::result_of_t<A0(int)> z = 6;
	std::cout << y << " " << z << std::endl;

	// std::result_of的基本用法
	typedef std::result_of<decltype(fn)&(int)>::type A; // int
	typedef std::result_of<fn_ref(int)>::type B;        // int
	typedef std::result_of<fn_ptr(int)>::type C;        // int
	typedef std::result_of<fn_class(int)>::type D;      // int
	std::cout << std::boolalpha << "typedef of int: " << std::endl;
	std::cout << "A: " << std::is_same<int, A>::value << std::endl;
	std::cout << "B: " << std::is_same<int, B>::value << std::endl;
	std::cout << "C: " << std::is_same<int, C>::value << std::endl;
	std::cout << "D: " << std::is_same<int, D>::value << std::endl;

	//// std::result_of要求模板是一个可调用对象，不是一个函数类型，
	//typedef std::result_of<decltype(fn)(int)>::type AA; // 这样使用函数类型是错误的

	typedef std::result_of<decltype(fn)&(int)>::type A1;
	typedef std::result_of<decltype(fn)*(int)>::type B1;
	typedef std::result_of<typename std::decay<decltype(fn)>::type(int)>::type C1;
	static_assert(std::is_same<A1, B1>::value, "not equal"); // true
	static_assert(std::is_same<A1, C1>::value, "not equal"); // true
	static_assert(std::is_same<B1, C1>::value, "not equal"); // true
}
// 3.1.4 根据条件禁用或启用某种或某些类型traits
template<typename T>
void Func03_01_08(T*) {
	std::cout << __FUNCTION__ << " A" << std::endl;
}
template<typename T>
void Func03_01_08(T) {
	std::cout << __FUNCTION__ << " B" << std::endl;
}
template<class T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type Func03_01_08C(T t) {
	return t;
}
// 对入参类型做限制，即第二个参数类型为integral
template <class T>
T Func03_01_08D(T t, typename std::enable_if<std::is_integral<T>::value, int>::type = 0) {
	return t;
}
template <class T, class = typename std::enable_if<std::is_integral<T>::value>::type>
T Func03_01_08E(T t) {
	return t;
}
template <class T, class Enable = void> class A8;
// 模板特化时,对模板参数做了限定，模板参数类型只能为浮点型
template <class T> class A8<T, typename std::enable_if<std::is_floating_point<T>::value>::type> {};
// std::enable_if利用SFINAE实现根据条件选择重载函数
void test03_01_08() {
	// 将匹配第二个重载函数 B，匹配第一个失败，继续匹配第二个，
    // 这个规则叫:SFINAE(substitutio failure is not an error),替换失败并非错误。
	Func03_01_08(1);

	// std::enable_if利用SFINAE实现根据条件选择重载函数
	// template<bool B, class T = void> struct enable_if;

	auto r1 = Func03_01_08C(1); // 返回整数1
	auto r2 = Func03_01_08C(1.2); // 返回浮点数1.2
	//auto r3 = Func03_01_08C("test"); // 编译错误
	auto r4 = Func03_01_08D(1, 5);
	auto r5 = Func03_01_08D(2, 1.5);  //warning C4244 : “参数”: 从“double”转换到“int”，可能丢失数据
	//auto r6 = Func03_01_08D(3, "test"); // 编译错误
	auto a1 = Func03_01_08E(4);
	//auto a2 = Func03_01_08E(1.2);  // 编译错误，

	A8<double> a;  // 编译通过
	//A8<int> b;    // 编译错误，不满足偏模板的限定条件，模板参数的类型应为浮点类型
}
// 通过判断式和非判断式将入参分为两大类
// 对于arithmetic类型的入参返回0，对于非arithmetic类型返回1，通过arithmetic将所有入参分成两个大类进行处理。
template <class T>
typename std::enable_if<std::is_arithmetic<T>::value, int>::type Func03_01_09A(T t) {
	std::cout << __FUNCTION__ << ": " << t << ", " << typeid(T).name() << std::endl;
	return 0;
}
template <class T>
typename std::enable_if<!std::is_arithmetic<T>::value, int>::type Func03_01_09A(T t) {
	std::cout << __FUNCTION__ << ": " << t << ", " << typeid(T).name() << std::endl;
	return 1;
}
void test03_01_09() {
	Func03_01_09A(1);
	Func03_01_09A("test09A");
}
// std::enable_if的第二个参数是默认模板参数void类型，因此，在函数没有返回值时，后面的模板参数可以省略
template <class T>
typename std::enable_if<std::is_arithmetic<T>::value>::type Func03_01_10A(T t) {
	std::cout << __FUNCTION__ << ": " << t << ", " << typeid(T).name() << std::endl;
}
template <class T>
typename std::enable_if<std::is_same<T, std::string>::value>::type Func03_01_10A(T t) {
	std::cout << __FUNCTION__ << ": " << t << ", " << typeid(T).name() << std::endl;
}
void test03_01_10() {
	Func03_01_10A(10);
	Func03_01_10A(std::string("test10A"));
}
// 
#include <sstream>
template <typename T>
std::string ToStringA(T t) {
	//std::cout << __FUNCTION__ << ": " << t << " " << typeid(T).name() << " " << typeid(t).name() << std::endl;
	if (typeid(T) == typeid(int) ||
		typeid(T) == typeid(double) ||
		typeid(T) == typeid(float)) {
		std::stringstream ss;
		ss << t;
		return ss.str();
	}
	else if (typeid(T) == typeid(std::string)) {
		//return t;  // 编译不过
		return "";
	}
	else {
		return std::string("");
	}
	return "";
}
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, std::string>::type ToStringB(T& t) {
	return std::to_string(t);
}
template <typename T>
typename std::enable_if<!std::is_arithmetic<T>::value, std::string>::type ToStringB(T& t) {
	return t;
}
void test03_01_11() {
	int a = 123;
	float b = 123.2;
	std::cout << __FUNCTION__ << " start" << std::endl;
	std::cout << ToStringA(a) << std::endl;
	std::cout << ToStringA(b) << std::endl;
	std::cout << ToStringA(std::string("A dddkdkdk")) << std::endl;
	std::cout << ToStringB(a) << std::endl;
	std::cout << ToStringB(b) << std::endl;
	std::cout << ToStringB("B dddkdkdk") << std::endl;
	std::cout << __FUNCTION__ << " end" << std::endl;
}

void test03_01() {
	test03_01_01();
	test03_01_02();
	test03_01_03();
	test03_01_04();
	test03_01_05();
	test03_01_06();
	test03_01_07();
	test03_01_08();
	test03_01_09();
	test03_01_10();
	test03_01_11();
	return;
}