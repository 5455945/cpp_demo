#include "C++11.03.h"
#include <iostream>
using namespace std;

// 3.1 �̳й��캯��
// �����嵥3-1
struct A { A(int i) { this->i = i; }  int i; };
struct B : A { B(int i) :A(i), d(i) {}; int d; };
// �����嵥3-2
struct A1 {
    A1(int i) { this->i = i; };
    A1(double d, int i) {};
    A1(float f, int i, const char* c) {}
    double d;
    int i;
    float f;
    const char* c;
};
struct B1 : A1 {
    B1(int i) : A1(i) {};
    B1(double d, int i) :A1(d, i) {}
    B1(float f, int i, const char* c) : A1(f, i, c) {}
    virtual void ExtraInterface();
};
// �����嵥3-3
struct Base {
    void f(double i) { cout << "Base::f " << i << endl; }
};
struct Derived :Base {
    using Base::f;
    void f(int i) { cout << "Derived::f " << i << endl; }
};
void Test_3_3() {
    Base b;
    b.f(4.5);
    Derived d;
    d.f(4.5);
    d.f(5);
}
// �����嵥3-4
struct A2 {
    A2(int i) { this->i = i; };
    A2(double d, int i) {};
    A2(float f, int i, const char* c) {}
    double d;
    int i;
    float f;
    const char* c;
};
struct B2 : A2 {
    using A2::A2;
    virtual void ExtraInterface();
};
void Test_3_4() {
    //B2 b2(3);
}

// �����嵥3-5
struct A3 {
    A3(int i) { };
    A3(double d, int i) {};
    A3(float f, int i, const char* c) {}
};
struct B3 : A3 {
    using A3::A3;
    virtual void ExtraInterface();
    int d{ 0 };
};
void Test_3_5() {
    //B3 b3(3);
}

// 3.2 ί�ɹ��캯��

// 3.3 ��ֵ���ã��ƶ����� �� ����ת��
// �����嵥3-18
class HasPtrMem {
public:
    HasPtrMem() : d(new int(0)) { cout << "construct: " << ++n_cstr << endl; }
    HasPtrMem(const HasPtrMem& h) : d(new int(*h.d)) { cout << "copy construct: " << ++n_cptr << endl; };
    virtual ~HasPtrMem() { cout << "destruct: " << ++n_dstr << endl; delete d; d = nullptr; }

    static int n_cstr;
    static int n_dstr;
    static int n_cptr;
private:
    int* d;
};
int HasPtrMem::n_cstr = 0;
int HasPtrMem::n_dstr = 0;
int HasPtrMem::n_cptr = 0;
HasPtrMem GetTemp() { return HasPtrMem(); }
void Test_3_18() {
    HasPtrMem a = GetTemp();
}

// �����嵥3-19
class HasPtrMem1 {
public:
    HasPtrMem1() : d(new int(3)) { cout << "construct: " << ++n_cstr << endl; }
    HasPtrMem1(const HasPtrMem1& h) : d(new int(*h.d)) { cout << "copy construct: " << ++n_cptr << endl; };
    HasPtrMem1(HasPtrMem1&& h) : d(h.d) { h.d = nullptr; cout << "move construct: " << ++n_mvtr << endl; };
    virtual ~HasPtrMem1() { cout << "destruct: " << ++n_dstr << endl; delete d; d = nullptr; }

    static int n_cstr;
    static int n_dstr;
    static int n_cptr;
    static int n_mvtr;
    int* d;
};
int HasPtrMem1::n_cstr = 0;
int HasPtrMem1::n_dstr = 0;
int HasPtrMem1::n_cptr = 0;
int HasPtrMem1::n_mvtr = 0;
HasPtrMem1 GetTemp1() {
    HasPtrMem1 h;
    cout << "resource from: " << __FUNCTION__ << hex << h.d << endl;
    return h;
}
void Test_3_19() {
    HasPtrMem1 a = GetTemp1();
    cout << "resource from: " << __FUNCTION__ << hex << a.d << endl;
}

// 3.4 ��ʽת��������

// 3.5 �б��ʼ��

// 3.6 POD����

// 3.7 ������������

// 3.8 �û��Զ���������

// 3.9 �������ֿռ�

// 3.10 ģ�����

// 3.11 һ�㻯��SFINEA����



void Test_C11_03() {
    Test_3_3();

    Test_3_18();
    Test_3_19();
    int n = 0;
}
