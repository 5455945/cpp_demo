#include "C++11.06.h"
#include <iostream>
#include <cstdarg>
#include <atomic>
#include <thread>
#include <Windows.h>
#include <cstdlib>
#include <cassert>
using namespace std;

// ������ ������ܼ�����Ӳ��������
// 6.1 �������ʽ
// 6.1.1 ����ʱ�����Լ�����ʱ������
//const int GetConst() { return 1; };
constexpr int GetConst() { return 1; };  // C++11��׼����ʱ�������ʽ��VS2013��֧��
void Constless(int cond) {
    int arr[GetConst()] = { 0 };     // �޷�����ͨ��
    enum { e1 = GetConst(), e2 };  // �޷�����ͨ��
    switch (cond) {
    case GetConst():                 // �޷�����ͨ��
        break;
    case 5:
        break;
    default:
        break;
    }
}
void Test_6_1() {
    Constless(1);
}
enum BitSet {
    V1 = 1 << 0,
    V2 = 1 << 1,
    V3 = 1 << 2,
    VMAX = 1 << 3
};
// �ض��� | ���������Ա�֤���ص�BitSetֵ������ö�����ֵ
const BitSet operator | (BitSet x, BitSet y) {
    return static_cast<BitSet>(((int)x | y) & (VMAX - 1));
}
template <int i = V0 | V1 >
void LikeConst() { cout << __FUNCTION__ << " " << __LINE__ << endl; };
void Test_6_2() {
    LikeConst<5>();
}

// 6.1.2 �������ʽ����
//constexpr int data() {const int i = 1; return i;}  // ������䣬���ǳ������ʽ����
//constexpr int f(int x) { static_assert(0 == 0, "fail"); return x; }  // static_assert�ǲ���ɵ���䣬�ǳ������ʽ����
//constexpr void f() {}  // û�з���ֵ�����ǳ������
//constexpr int f() { return 5; }
void Test_6_3() {
    //constexpr int f();
    //int a = f();
    //const int b = f();
    //constexpr int c = f();  // Ҫ�����ʱ����f()��ֵ����f��û�ж��壬�޷�����ͨ��
    //constexpr int d = f();
}
//const int e() {return 0;}
//constexpr int func1() { return e(); }  // ���Ϸ���e()���ǳ������ʽ
//int g = 3;
//constexpr int func2() {return g;}  // ���Ϸ���g���ǳ������ʽ
//constexpr int func3(int x) { return x = 3; }  // ���Ϸ���������return�н��и�ֵ����

// 6.1.3 �������ʽ��ֵ
void Test_6_4() {
    struct MyType {
        MyType(int x) : i(x) {}
        int i;
    };
    //constexpr MyType mt = {0};
}

struct Date {
    constexpr Date(int y, int m, int d) : year(y), month(m), day(d) {};
    constexpr int GetYear() const{ return year; }
    constexpr int GetMonth() const { return month; }
    constexpr int GetDay() const{ return day; }
private:
    int year;
    int month;
    int day;
};
void Test_6_5() {
    constexpr Date PRCfound{ 1949, 10, 1 };
    //Date PRCfound(1949, 10, 1);
    constexpr int foundMonth = PRCfound.GetMonth();
    cout << "foundMonth: " << foundMonth << endl;
}
// 6.1.4 �������ʽ������Ӧ��
struct NotLiteral {
    NotLiteral() { i = 5; }
    int i;
};

template <typename T> constexpr T ConstExp(T t) { return t; };
//template <typename T> T ConstExp(T t) { return t; };
void Test_6_6() {
    NotLiteral nl;
    NotLiteral nl1 = ConstExp(nl);
    //constexpr NotLiteral nl2 = ConstExp(nl);
    constexpr int n2 = ConstExp(1);
}
constexpr int fibonacci(int n) {
    return (n == 1) ? 1 : ((n == 2) ? 1 : fibonacci(n - 1) + fibonacci(n - 2));
}
//int fibonacci(int n) {
//    return (n == 1) ? 1 : ((n == 2) ? 1 : fibonacci(n - 1) + fibonacci(n - 2));
//}

void Test_6_7() {
    int fib[] = {
        fibonacci(11), fibonacci(12),
        fibonacci(13), fibonacci(14),
        fibonacci(15), fibonacci(16)
    };
    for (int i : fib) {
        cout << i << " ";
    }
    cout << endl;
}

// ģ��Ԫ���
template <long num>
struct Fibonacci {
    static const long val = Fibonacci<num - 1>::val + Fibonacci<num - 2>::val;
};
template <> struct Fibonacci<2> { static const long val = 1; };
template <> struct Fibonacci<1> { static const long val = 1; };
template <> struct Fibonacci<0> { static const long val = 0; };
void Test_6_8() {
    int fib[] = {
        Fibonacci<11>::val, Fibonacci<12>::val,
        Fibonacci<13>::val, Fibonacci<14>::val,
        Fibonacci<15>::val, Fibonacci<16>::val
    };
    for (int i : fib) {
        cout << i << " ";
    }
    cout << endl;
}

// 6.2 �䳤ģ��
// 6.2.1 �䳤������䳤ģ�����
double SumOfFloat(int count, ...) {
    double sum = 0;
    va_list ap;
    va_start(ap, count);
    for (int i = 0; i < count; ++i) {
        sum += va_arg(ap, double);
    }
    va_end(ap);
    return sum;
}
void Test_6_9() {
    cout << SumOfFloat(2.3f, 3.4f, 4.5f, 5.6) << endl;
}

// 6.2.2 ���ģ�壺ģ��������ͺ���������
//template <typename ... Elemnets> class tuple;
//tuple <int, char, double>;
//template <int ... A> class NotTypeVariadicTemplate{};
//NotTypeVariadicTemplate<1, 0, 2> ntvt;

// �����嵥6-10
template <typename ... Elemnets> class tuple1;
template <typename Head, typename ... Tail> // �ݹ��ƫ�ػ�����
class tuple1<Head, Tail ...> : private tuple1 < Tail ... > {
    Head head;
};
template <> class tuple1<> {};

// �����嵥6-11
template<long ... nums> struct Multiply;
template<long first, long ... last>
struct Multiply < first, last... > {
    static const long val = first * Multiply<last...>::val;
};
template<> struct Multiply<> { static const long val = 1; };
void Test_6_11() {
    cout << Multiply<2, 3, 4, 5>::val << endl;
    cout << Multiply<22, 44, 66, 88, 9>::val << endl;
}
// T�Ǳ䳤ģ�������args�Ǳ䳤����������
// C++11Ҫ�󣺺�������������Ψһ���ұ����Ǻ��������һ��������ģ�������û���Ҫ��
//template <typename ...T> void f(T ...args);
void Printf(const char* s) {
    while (*s) {
        if (*s == '%' && *++s != '%') {
            throw runtime_error("invalid format string: missing arguments.");
        }
        cout << *s++;
    }
}
// ����޸���Ӧ���ܱȽ�������s�ĳ�string wstring���͵�
template <typename T, typename ...Args>
void Printf(const char* s, T value, Args ... args) {
    while (*s) {
        if (*s == '%' && *++s != '%') {
            cout << value;
            return Printf(++s, args...);
        }
        cout << *s++;
    }
    throw runtime_error("extra arguments provided to Printf");
}
void Test_6_12() {
    Printf("Hello %s\n", string("World!").c_str());
}

// 6.2.3 �䳤ģ�壺����
template <typename ... T> void DummyWrapper(T ... t) {};
template <typename T> T pr(T t) {
    cout << t;
    return t;
};

template <typename ...A>
void VTPrint(A ... a) {
    DummyWrapper(pr(a)...);
};
void Test_6_13() {
    VTPrint(1, ", ", 1.2, ", abc\n");  // ��vs2013�����ӡ˳���ˣ����ҵ����������˳��
    cout << endl;
}

// 6.3 ԭ��������ԭ�Ӳ���
// 6.3.1 ���б�̡����߳���C++11
// 6.3.2 ԭ�Ӳ�����C++11��ԭ������
atomic_llong total{ 0 };  // total��ԭ������
long long g_total{ total };  // g_total ����ԭ������

void func(int) {
    for (long long i = 0; i < 1000000LL; ++i) {
        total += i;
    }
}

void func2(int) {
    for (long long i = 0; i < 1000000LL; ++i) {
        g_total += i;
    }
}

void Test_6_19() {
    thread t1(func, 0);
    thread t2(func, 0);
    t1.join();
    t2.join();

    thread t3(func2, 0);
    thread t4(func2, 0);
    t3.join();
    t4.join();

    cout << "total = " << total << endl;
    cout << "g_total = " << g_total << endl;
}
// ԭ������ֻ�ܴ���ģ������й��죬��׼�����������캯�����ƶ��������캯������ֵ������=����
void Test_6_19_1() {
    atomic<float> af{ 1.2f };  // ��ȷ
    //atomic<float> af1{af};   // ���󣬿������캯���Ѿ�ɾ��
    float a = af;  // ��ȷ������ת����a ����ԭ������
    float b{ af };   // ��ȷ������ת����b ����ԭ������
}
atomic_flag lock = ATOMIC_FLAG_INIT;
void f(int n) {
    while (lock.test_and_set(std::memory_order_acquire)) {  // ���Ի����
        cout << "Waiting from thread " << n << endl;  // ����
    }
    cout << "Thread " << n << " starts working" << endl;
}
void g(int n) {
    cout << "Thread " << n << " is going to start." << endl;
    lock.clear();
    cout << "Thread " << n << " starts working" << endl;
}
void Test_6_20() {
    lock.test_and_set();
    thread t1(f, 1);
    thread t2(g, 2);
    t1.join();
    //usleep(100);
    ::Sleep(100);
    t2.join();
    //t2.detach();
    //t1.join();
}
// 6.3.3 �ڴ�ģ�ͣ�˳��һ������memory_order
atomic<int> a{ 0 };
atomic<int> b{ 0 };
int ValueSet(int x) {
    int t = 1;
    a = t;
    b = 2;
    return 0;
}
void Observer(int n) {
    cout << "a = " << a << " b = " << b << endl;
}
void Test_6_21() {
    thread t1(ValueSet, 0);
    thread t2(Observer, 0);
    t1.join();
    t2.join();
    cout << "Got a = " << a << " b = " << b << endl;
}
// C++11 ��ԭ����������Ĭ���� ��˳��һ�¡� ��
void Test_6_22() {
    atomic<int> a{ 0 };
    atomic<int> b{ 0 };
    thread t1([&](int n) {int t = 1; a = t; b = 2; }, 0);
    thread t2([&](int n) {
        while (b != 2);    // ����
        cout << a << endl; },  // ��������a��ʾ1
        0);
    t1.join();
    t2.join();
}

void Test_6_23() {  // 21�ĸ���
    atomic<int> a{ 0 };
    atomic<int> b{ 0 };
    thread t1([&](int n) {int t = 1; a.store(t, std::memory_order_relaxed); b.store(2, std::memory_order_relaxed); }, 0);
    thread t2([&](int n) {cout << "a = " << a << " b = " << b << endl; },
        0);
    t1.join();
    t2.join();
    cout << "Got a = " << a << " b = " << b << endl;
}

void Test_6_24() {  // Test_6_22 ��
    atomic<int> a{ 0 };
    atomic<int> b{ 0 };
    thread t1([&](int n) {int t = 1; a.store(t, std::memory_order_relaxed); b.store(2, std::memory_order_relaxed); }, 0);
    thread t2([&](int n) {
        while (b.load(std::memory_order_relaxed) != 2);    // ����
        cout << a.load(std::memory_order_relaxed) << endl; },  // ��������a��ʾ1
        0);
    t1.join();
    t2.join();
}

void Test_6_25() {  // Test_6_24 ��
    atomic<int> a{ 0 };
    atomic<int> b{ 0 };
    thread t1([&](int n) {int t = 1;
    a.store(t, std::memory_order_relaxed);
    b.store(2, std::memory_order_release); },   // ��ԭ�Ӳ���ǰ����дԭ�Ӳ����������
        0);
    thread t2([&](int n) {
        while (b.load(std::memory_order_acquire) != 2);    // ��ԭ�Ӳ���������ɲ���ִ��֮�����еĶ�ԭ�Ӳ���
        cout << a.load(std::memory_order_relaxed) << endl; },  // ��������a��ʾ1
        0);
    t1.join();
    t2.join();
}

void Test_6_26() {
    atomic<string*> pstr;
    atomic<int> data;
    auto producer = [&]() {
        string* p = new string("hello");
        data.store(42, std::memory_order_relaxed);
        pstr.store(p, std::memory_order_release);
    };
    auto consumer = [&]() {
        string* p2 = nullptr;
        while (!(p2 = pstr.load(std::memory_order_consume)));
        assert(*p2 == "hello");  // �������
        assert(data.load(memory_order_relaxed) == 42);  // ���ܶ���ʧ��
    };

    thread t1(producer);
    thread t2(consumer);
    t1.join();
    t2.join();
}

// 6.4 �ֲ߳̾��洢
void Test_6_26_0() {
    //int thread_local errCode;  // vs2013��֧�� thread_local
}
// 6.5 �����˳���quick_exit �� at_quick_exit
void openDevice() { cout << "device is opened." << endl; }
void resetDeviceStat() { cout << "device stat is reset." << endl; }
void closeDevice() { cout << "device is closed." << endl; }
void Test_6_28() {
    atexit(closeDevice);
    atexit(resetDeviceStat);
    openDevice();
    exit(0);
}
struct A {
    ~A() { cout << "Destruct A::~A()" << endl; }
};
void Test_6_29() {
    A a;
    at_quick_exit(closeDevice);
    quick_exit(0);
}
void Test_C11_06() {
    cout << __FUNCTION__ << " begin" << endl;
    Test_6_1();
    Test_6_2();
    Test_6_3();
    Test_6_4();
    Test_6_5();
    Test_6_6();
    Test_6_7();
    Test_6_8();
    Test_6_9();
    Test_6_11();
    Test_6_12();
    Test_6_13();
    Test_6_19();
    Test_6_19_1();
    Test_6_20();
    //for (int i = 0; i < 100; i++) {
    //Test_6_21();
    //Test_6_22();
    //Test_6_23();
    //Test_6_24();
    //}
    Test_6_21();
    Test_6_22();
    Test_6_23();
    Test_6_24();
    Test_6_25();
    Test_6_26();
    //Test_6_28();
    //Test_6_29();

    cout << __FUNCTION__ << " end" << endl;
}
