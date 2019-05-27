#include "C++11.05.h"
#include <iostream>
#include <memory>
using namespace std;

// 5.1 强类型枚举
void Test_5_0() {
    enum Gender { Male, Female };  // 传统C的枚举方式，命名枚举
    // 使用宏定义的方式
#define Male1   0
#define Female1 1
// 匿名定义枚举类型
    enum { Male2, Female2 };
    // 静态常量
    static const int Male3 = 0;
    static const int Female3 = 1;

    // 传统C的enum定义类型和值全局可见，已发生冲突
    //enum Type {Ganeral, Light, Medium, Heavy};
    //enum Category {Ganeral, Pistol, MachineGun, Cannon};  // Ganeral重定义，以前的定义是“枚举数”

    // C++11 采用强类型定义，不会发生冲突
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
    if (t == Ganeral) {  // 忘记使用namespace
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
    //t = Ganeral;  // 未定义的标识符 Ganeral
    //if (t == Category::Ganeral) {  // Category::Ganeral 和t类型不同
    //    cout << "Ganeral Weapon" << endl;
    //}
    if (t >= Type::Ganeral) {
        cout << "Not Ganeral Weapon" << endl;
    }
    //if (t > 0) {  // t的类型不是int
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

    // C++11对原有枚举类型的扩展
    enum Type : char { Ganeral = 'c', Light, Medium, Heavy };
    Type t = Light;
    t = Type::Medium;  // C++11中，老的定义形式，也可以使用作用域方式

    // 新的枚举类型也可以使用struct代替class，效果完全相同
    enum struct Type1 : char { Ganeral = 'c', Light, Medium, Heavy };
}
// 匿名class什么也做不了
void Test_5_7() {
    // vs2013要求区分范围的枚举必须具名，强类型枚举必须有类型名称
    //enum class { Ganeral, Light, Medium, Heavy } weapon;  // 编译错误
    //enum struct { Ganeral, Light, Medium, Heavy } weapon;  // 编译错误
}
// 5.2 堆内存管理：智能指针和垃圾回收
// 5.2.1 显示内存管理
// 5.2.2 C++11的智能指针
void Test_5_8() {
    unique_ptr<int> up1(new int(11));  // 无法复制的unique_ptr
    //unique_ptr<int> up2 = up1;         // 无法复制unique_ptr，复制构造已经被删除
    cout << *up1 << endl;              // 11
    unique_ptr<int> up3 = move(up1);   // 现在up3是数据唯一的unique_ptr智能指针
    cout << *up3 << endl;              // 11
    //cout << *up1 << endl;              // 运行时错误
    up3.reset();                       // 显示释放内存
    up1.reset();                       // 不会导致错误
    //cout << *up3 << endl;              // 运行时错误

    shared_ptr<int> sp1(new int(22));
    shared_ptr<int> sp2 = sp1;
    cout << *sp1 << endl;  // 22
    cout << *sp2 << endl;  // 22
    sp1.reset();
    //cout << *sp1 << endl;  // 运行时错误，sp1已经释放，empty() == true
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
    // weak_ptr 弱指针
    // weak_ptr 指向shared_ptr指针的实体对象，而不拥有这个对象，可以理解为一个纯指针或者指针的别名
    weak_ptr<int> wp = sp1;  // 指向shared_ptr所指对象
    cout << *sp1 << endl;    // 22
    cout << *sp2 << endl;    // 22
    Check(wp);               // still: 22

    sp1.reset();
    cout << *sp2 << endl;    // 22
    Check(wp);               // still: 22

    sp2.reset();
    Check(wp);               // pointer is invalid.
}
// 在 C++11 / 14 中弃用以及在 C++17 中移除 auto_ptr、 random_shuffle() 和 old <functional>。 
// 默认情况下，Visual Studio 2015 提供它们，但是将 _HAS_AUTO_PTR_ETC 定义为 0 的项目范围将移除它们的定义。

// 5.2.3 垃圾回收的分类

// 5.2.4 C++与垃圾回收
void Test_5_10() {
    int* p = new int;
    p += 10;
    p -= 10;
    *p = 10;
}
void Test_5_11() {
    int* p = new int;
    int* q = (int*)(reinterpret_cast<long long>(p) ^ 2012);  // q 隐藏了 p
    // 做一些其他工作，垃圾回收器可能已经回收了p
    q = (int*)(reinterpret_cast<long long>(q) ^ 2012);  // 这里的q == p;
    *q = 10;
}
// 5.2.5 C++11 与最小垃圾回收支持
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
    declare_reachable((void*)p);   // 在p隐藏之前声明为可达的
    int* q = (int*)((long long)p ^ 2012);
    // 解除可达声明
    q = undeclare_reachable<int>((int*)((long long)q ^ 2012));
    *q = 10;

    //void declare_no_pointers(char* p, size_t n) noexcept;
    //void undeclare_no_pointers(char* p, size_t n) noexcept;
}
// 5.2.6 垃圾回收的兼容性

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
