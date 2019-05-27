#include "C++11.05.h"
#include <iostream>
#include <memory>
using namespace std;

// 5.1 ǿ����ö��
void Test_5_0() {
    enum Gender { Male, Female };  // ��ͳC��ö�ٷ�ʽ������ö��
    // ʹ�ú궨��ķ�ʽ
#define Male1   0
#define Female1 1
// ��������ö������
    enum { Male2, Female2 };
    // ��̬����
    static const int Male3 = 0;
    static const int Female3 = 1;

    // ��ͳC��enum�������ͺ�ֵȫ�ֿɼ����ѷ�����ͻ
    //enum Type {Ganeral, Light, Medium, Heavy};
    //enum Category {Ganeral, Pistol, MachineGun, Cannon};  // Ganeral�ض��壬��ǰ�Ķ����ǡ�ö������

    // C++11 ����ǿ���Ͷ��壬���ᷢ����ͻ
    enum class Type { Ganeral, Light, Medium, Heavy };
    enum class Category { Ganeral, Pistol, MachineGun, Cannon };
    int n = sizeof(Type);
    int m = sizeof(Category);
    int k = sizeof(Gender);

    enum class Category1 :char { Ganeral, Pistol, MachineGun, Cannon };
}
namespace T {
    enum Type { Ganeral, Light, Medium, Heavy };
}
namespace {
    enum Category { Ganeral, Pistol, MachineGun, Cannon };
}
void Test_5_1() {
    T::Type t = T::Light;
    if (t == Ganeral) {  // ����ʹ��namespace
        cout << "Ganeral Weapon" << endl;
    }
    else {
        cout << "t != Ganeral" << endl;
    }
}
void Test_5_5() {
    enum class Type { Ganeral, Light, Medium, Heavy };
    enum class Category { Ganeral, Pistol, MachineGun, Cannon };
    Type t = Type::Ganeral;
    //t = Ganeral;  // δ����ı�ʶ�� Ganeral
    //if (t == Category::Ganeral) {  // Category::Ganeral ��t���Ͳ�ͬ
    //    cout << "Ganeral Weapon" << endl;
    //}
    if (t >= Type::Ganeral) {
        cout << "Not Ganeral Weapon" << endl;
    }
    //if (t > 0) {  // t�����Ͳ���int
    //    cout << "Not Ganeral Weapon" << endl;
    //}
    if ((int)t > 0) {
        cout << "Not Ganeral Weapon" << endl;
    }
    cout << is_pod<Type>::value << endl;
    cout << is_pod<Category>::value << endl;
}
void Test_5_6() {
    enum class C : char { C1 = 1, C2 = 2 };
    enum class D : unsigned int { D1 = 1, D2 = 2, Dbig = 0xFFFFFFF0U };
    cout << sizeof(C::C1) << endl;  // 1
    cout << (unsigned int)D::Dbig << endl;  // 0xFFFFFFF0
    cout << sizeof(D::D1) << endl;  // 4
    cout << sizeof(D::Dbig) << endl;  // 4

    // C++11��ԭ��ö�����͵���չ
    enum Type : char { Ganeral = 'c', Light, Medium, Heavy };
    Type t = Light;
    t = Type::Medium;  // C++11�У��ϵĶ�����ʽ��Ҳ����ʹ��������ʽ

    // �µ�ö������Ҳ����ʹ��struct����class��Ч����ȫ��ͬ
    enum struct Type1 : char { Ganeral = 'c', Light, Medium, Heavy };
}
// ����classʲôҲ������
void Test_5_7() {
    // vs2013Ҫ�����ַ�Χ��ö�ٱ��������ǿ����ö�ٱ�������������
    //enum class { Ganeral, Light, Medium, Heavy } weapon;  // �������
    //enum struct { Ganeral, Light, Medium, Heavy } weapon;  // �������
}
// 5.2 ���ڴ��������ָ�����������
// 5.2.1 ��ʾ�ڴ����
// 5.2.2 C++11������ָ��
void Test_5_8() {
    unique_ptr<int> up1(new int(11));  // �޷����Ƶ�unique_ptr
    //unique_ptr<int> up2 = up1;         // �޷�����unique_ptr�����ƹ����Ѿ���ɾ��
    cout << *up1 << endl;              // 11
    unique_ptr<int> up3 = move(up1);   // ����up3������Ψһ��unique_ptr����ָ��
    cout << *up3 << endl;              // 11
    //cout << *up1 << endl;              // ����ʱ����
    up3.reset();                       // ��ʾ�ͷ��ڴ�
    up1.reset();                       // ���ᵼ�´���
    //cout << *up3 << endl;              // ����ʱ����

    shared_ptr<int> sp1(new int(22));
    shared_ptr<int> sp2 = sp1;
    cout << *sp1 << endl;  // 22
    cout << *sp2 << endl;  // 22
    sp1.reset();
    //cout << *sp1 << endl;  // ����ʱ����sp1�Ѿ��ͷţ�empty() == true
    cout << *sp2 << endl;  // 22
}
void Check(weak_ptr<int>& wp) {
    shared_ptr<int> sp = wp.lock();
    if (sp != nullptr) {
        cout << "still: " << *sp << endl;
    }
    else {
        cout << "pointer is invalid." << endl;
    }
}
void Test_5_9() {
    shared_ptr<int> sp1(new int(22));
    shared_ptr<int> sp2 = sp1;
    // weak_ptr ��ָ��
    // weak_ptr ָ��shared_ptrָ���ʵ����󣬶���ӵ��������󣬿������Ϊһ����ָ�����ָ��ı���
    weak_ptr<int> wp = sp1;  // ָ��shared_ptr��ָ����
    cout << *sp1 << endl;    // 22
    cout << *sp2 << endl;    // 22
    Check(wp);               // still: 22

    sp1.reset();
    cout << *sp2 << endl;    // 22
    Check(wp);               // still: 22

    sp2.reset();
    Check(wp);               // pointer is invalid.
}
// �� C++11 / 14 �������Լ��� C++17 ���Ƴ� auto_ptr�� random_shuffle() �� old <functional>�� 
// Ĭ������£�Visual Studio 2015 �ṩ���ǣ����ǽ� _HAS_AUTO_PTR_ETC ����Ϊ 0 ����Ŀ��Χ���Ƴ����ǵĶ��塣

// 5.2.3 �������յķ���

// 5.2.4 C++����������
void Test_5_10() {
    int* p = new int;
    p += 10;
    p -= 10;
    *p = 10;
}
void Test_5_11() {
    int* p = new int;
    int* q = (int*)(reinterpret_cast<long long>(p) ^ 2012);  // q ������ p
    // ��һЩ�������������������������Ѿ�������p
    q = (int*)(reinterpret_cast<long long>(q) ^ 2012);  // �����q == p;
    *q = 10;
}
// 5.2.5 C++11 ����С��������֧��
void Test_5_12() {
    pointer_safety p1 = get_pointer_safety();
    switch (p1) {
    case pointer_safety::preferred:
        cout << "pointer_safety == pointer_safety::preferred: " << (int)pointer_safety::preferred << endl;
        break;
    case pointer_safety::relaxed:
        cout << "pointer_safety == pointer_safety::relaxed: " << (int)pointer_safety::relaxed << endl;
        break;
    case pointer_safety::strict:
        cout << "pointer_safety == pointer_safety::strict: " << (int)pointer_safety::strict << endl;
        break;
    default:
        break;
    }
    int* p = new int;
    declare_reachable((void*)p);   // ��p����֮ǰ����Ϊ�ɴ��
    int* q = (int*)((long long)p ^ 2012);
    // ����ɴ�����
    q = undeclare_reachable<int>((int*)((long long)q ^ 2012));
    *q = 10;

    //void declare_no_pointers(char* p, size_t n) noexcept;
    //void undeclare_no_pointers(char* p, size_t n) noexcept;
}
// 5.2.6 �������յļ�����

void Test_C11_05() {
    cout << __FUNCTION__ << " begin" << endl;
    Test_5_0();
    Test_5_1();
    Test_5_5();
    Test_5_6();
    Test_5_7();
    Test_5_8();
    Test_5_9();
    Test_5_10();
    Test_5_11();
    Test_5_12();

    cout << __FUNCTION__ << " end" << endl;
}
