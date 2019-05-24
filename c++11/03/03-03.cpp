#include "03-03.h"
#include <iostream>
#include <string>
#include <functional>
#include <optional> // std:c++17
#include "Optional.hpp"
#include "Lazy.hpp"
#include "DllParser.hpp"
#include "LambdaChain.hpp"
#include "Any.hpp"
#include "function_traits.hpp"
#include "ScopeGuard.hpp"

// 3.3 可变参数模板和type_taits的综合应用
// 3.3.1 optional的实现
void test03_03_01() {
    std::optional<int> op;
    if (op) {
        std::cout << "*op = " << *op << std::endl;
    }

    std::optional<int> op1 = 1;
    if (op1) {
        std::cout << "*op1 = " << *op1 << std::endl;
    }
}

void test03_03_02() {
    struct A {
        int avg;
        A(int a, int b) : avg((a + b) / 2) {}
    };
    typedef std::aligned_storage<sizeof(A), alignof(A)>::type Aligned_A;
    Aligned_A a, b;
    new (&a) A(10, 20); // placement new
    b = a;
    std::cout << reinterpret_cast<A&>(b).avg << std::endl;
}

// Optional<T> op,内部存储空间可能存储了T类型的值，也可能没有存T类型的值；
// 只有当optional被T初始化之后，这个optional才有效，否则无效。它实现了未初始化的概念。
void test03_03_03() {
    struct MyStruct {
        MyStruct::MyStruct() = default;
        MyStruct(int a, int b) :m_a(a), m_b(b) {}
        int m_a;
        int m_b;
    };
    Optional<std::string> a("ok");
    Optional<std::string> b("ok");
    Optional<std::string> c;
    if (c) {
        std::cout << " c 已初始化！" << std::endl;
    }
    else {
        std::cout << " c 未初始化！" << std::endl;
    }
    c = a;

    Optional<MyStruct> op;
    op.emplace(1, 2);
    struct MyStruct t;
    if (op) { // 判断optional是否被初始化
        t = *op;
    }
    op.emplace(3, 4);
    t = *op;
}
// 3.3.2 惰性求值类lazy的实现
void test03_03_04() {
    struct BigObject {
        BigObject() {
            std::cout << "lazy load big object" << std::endl;
        }
    };
    struct MyStruct {
        MyStruct() {
            m_obj = lazy([] {return std::make_shared<BigObject>(); });
        }
        void Load() {
            m_obj.Value();
        }
        Lazy<std::shared_ptr<BigObject>> m_obj;
    };
    auto Foo = [](int x) { return x * 2; };
    // 带参数的普通对象
    int y = 4;
    auto lazyer1 = lazy(Foo, y);
    std::cout << lazyer1.Value() << std::endl;
    // 不带参数的lambda
    Lazy<int> lazyer2 = lazy([] {return 2; });
    std::cout << lazyer2.Value() << std::endl;
    // 带参数的function
    std::function<int(int)> f = [](int x){ return x + 3; };
    auto lazyer3 = lazy(f, 3);
    std::cout << lazyer3.Value() << std::endl;
    // 延迟加载大对象
    MyStruct t;
    t.Load();
}

// 3.3.3 dll帮助类
void test03_03_05() {
    DllParser dllParser;
    dllParser.Load("kernel32.dll");
    char szComputerName[256];
    memset(szComputerName, 0, sizeof(szComputerName));
    ////DWORD GetVersion(); 调用kernel32.dll的GetVersion函数
    //dllParser.GetFunction<DWORD(void)>("GetVersion");
    DWORD dwVersion = dllParser.ExcecuteFunc<DWORD(void)>("GetVersion");
    std::cout << dwVersion << std::endl;
}

// 3.3.4 lambda的链式调用
void test03_03_06() {
    LambdaChain<int(int)> task = [](int i) { return i; };
    auto result = task.Then([](int i) {return i + 1; }).Then([](int i) {
        return i + 2; }).Then([](int i) {return i + 3; }).Run(1);
    std::cout << result << std::endl;  // 7
}

// 3.3.5 Any类的实现
void test03_03_07() {
    Any n;
    auto r = n.IsNull(); // true;
    std::string s1 = "hello";
    n = s1;
    //n.AnyCast<int>(); // 转换失败将抛出异常
    Any n1 = 1;
    n1.Is<int>(); // true
}

// 3.3.6 function_traits
template<typename T>
void PrintType() {
    std::cout << typeid(T).name() << std::endl;
}
float(*castfunc)(std::string, int);
float free_function(const std::string& a, int b) {
    return (float)a.size() / b;
}
struct AA {
    int f(int a, int b) volatile { return a + b; }
    int operator()(int) const { return 0; }
};
void test03_03_08() {
    std::function<int(int)> f = [](int a) { return a; };
    PrintType<function_traits<std::function<int(int)>>::function_type>();
    PrintType<function_traits<std::function<int(int)>>::args<0>::type>();
    PrintType<function_traits<decltype(f)>::function_type>();
    PrintType<function_traits<decltype(free_function)>::function_type>();
    PrintType<function_traits<AA>::function_type>();
    using T = decltype(&AA::f);
    PrintType<T>();
    PrintType<function_traits<decltype(&AA::f)>::function_type>();
    static_assert(std::is_same<function_traits<decltype(f)>::return_type, int>::value, "");
}

// 3.3.8 ScopeGuard
void test03_03_10() {
    std::function < void()> f = []()
    { std::cout << "cleanup from unnormal exit" << std::endl; };
    // 正常退出
    {
        auto gd = MakeGuard(f);
        //...
        gd.Dismiss();  // 表明前面我是正常的清理了资源，属于正常退出的
    }
    
    // 异常退出
    try
    {
        auto gd = MakeGuard(f);
        // ...
        throw 1;
    }
    catch (...)
    {
        std::cout << "捕获到了一个异常！！\n\n";
    }

    // 非正常退出
    {
        auto gd = MakeGuard(f);
        return;  // 非正常退出表示资源还没清理呢，，等着ScopeGuard自动清理
        // ...
    }
}
void test03_03() {
    test03_03_01();
    test03_03_02();
    test03_03_03();
    test03_03_04();
    test03_03_05();
    test03_03_06();
    test03_03_07();
    test03_03_08();
    test03_03_10();  // 测试异常
    return;
}