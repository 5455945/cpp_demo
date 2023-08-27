#include "02-01.h"

// 1、特性一、Deducing this
// Deducing this是C++23中最重要的特性之一，它于2022年03月份被msvc支持，并可在v19.32版本之后使用。
// 成员函数都有一个隐式对象参数，对于非静态成员函数，这个隐式对象参数就是指向对象的this指针。
// 而对于静态成员函数，这个隐式对象参数被定义为可以匹配任何参数，这仅仅是为了保证重载决议可以正常运行。
// Deducing this所做的事情则是提供了一种将非静态成员函数的“隐式对象参数”变为“显式对象参数”的方法。
// 为什么只针对非静态成员函数呢？因为静态成员函数并没有this指针，隐式对象参数并不能和this指针划等号，
// 静态函数拥有隐式对象参数只是保证重载决议能够正常运行而已，这个参数没有其他用处。


// 通过Deducing this，我们可以将隐式对象参数显式地写出来，语法为this+type。
struct S_implicit0 {
    void foo() {}
};

struct S_explicit1 {
    void foo(this S_explicit1&) {}
};


// 这个提案的根本动机是消除成员函数修饰所带来的冗余。举个例子：
// Before
struct S_implicit_Before {
    int data_;

    int& foo()& { return data_; }
    const int& foo() const& { return data_; }
};

// After
#include <utility> // std::forward
struct S_explicit_After {
    int data_;

    template <class Self>
    auto&& foo(this Self& self) {
        return std::forward<Self>(self).data_;
    }
};

void test02_01_01() {
    S_implicit0 s1;
    S_explicit1 s2;
    S_implicit_Before s3;
    S_explicit_After s4;
    s1.foo();
    s2.foo();
    s3.foo();
    s4.foo();
}

// 使用Deducing this，您不再需要为同一个成员函数编写各种版本的修饰，例如&, const&, &&, const&& 等，
// 因为它们的逻辑并没有太大的变化，完全是重复的机械式操作。
// 现在，您只需要编写一个版本即可。 具体来说，我们可以使用模板形式的参数，
// 通常建议使用Self作为显式对象参数的名称，这不仅顾名思义，而且与其他语言保持一致性。 
// 除此之外，Deducing this还有许多其他的使用场景，同时也是一种新的定制点表示方式。
// 例如，利用Deducing this可以实现递归Lambdas。

#include <iostream> // std::cout
void test02_01_02() {
    auto gcd = [](this auto self, int a, int b) -> int {
        return b == 0 ? a : self(b, a % b);
    };

    std::cout << gcd(20, 30) << "\n";
}


//借助Deducing this，Lambda函数得到了增强。在过去，递归Lambdas很难实现，但是使用Deducing this可以轻松地实现这一点。

// 此外，Deducing this还可以简化CRTP（Curiously Recurring Template Pattern）。CRTP通常用于C++中的静态多态性，
// 并且它要求派生类继承一个模板基类并将自身作为模板参数传递。通过使用Deducing this，
// 在模板基类中不再需要显式指定派生类类型，而是可以通过推断this指针来推导出派生类类型。
// 这使得CRTP代码更加简洁和易于理解。
namespace n02_01_03{
    //// Before
    // CRTP
    template <class Derived>
    struct Base {
        void foo() {
            auto& self = *static_cast<Derived*>(this);
            self.bar();
        }
    };

    struct Derived : Base<Derived> {
        void bar() const {
            std::cout << "CRTP Derived\n";
        }
    };

    ////////////////////////////////////////////
    //// After
    // Deducing this
    struct Base2 {
        template <class Self>
        void foo(this Self&& self) {
            std::cout << __func__ << "\n";
            self.bar();
        }
        void test() {
            std::cout << __func__ << "\n";
        }
    };

    struct Derived2 : Base2 {
        void bar() const {
            std::cout << __func__ << " Deducing this Derived\n";
        }
    };

    struct Base3 {
        template <class Self>
        void f(this Self&& self) {
            self.f2();
            std::cout << __func__ << " Deducing this f()\n";
        }
    };

    struct Derived3 : Base3 {
        void f2() {
            std::cout << __func__ << "\n";
      }
    };
}

void test02_01_03() {
    n02_01_03::Derived d;
    n02_01_03::Base<n02_01_03::Derived> b;
    b.foo();
    d.bar();
    std::cout << __func__ << " =====\n";
    n02_01_03::Derived2 d2;
    n02_01_03::Base2 b2;
    //n02_01_03::Base2 b2(d2);
    b2.test();
    //b2.foo<n02_01_03::Derived2>();
    d2.bar();
    d2.foo();
    std::cout << __func__ << " =====\n";
    n02_01_03::Derived3 d3;
    d3.f();
    std::cout << __func__ << " =====\n";
}

// 采用这种新的方式实现CRTP，能够省去CR和T，使得代码更加自然、清晰。此外，这也是一种全新的定制点方式。以下为简单的例子：
// Library
namespace mylib {

    struct S {
        auto abstract_interface(this auto& self, int param) {
            self.concrete_algo1(self.concrete_algo2(param));
        }
    };
} // namespace mylib

namespace userspace {
    struct M : mylib::S {
        auto concrete_algo1(int val) {}
        auto concrete_algo2(int val) const {
            return val * 6;
        }
    };
} // namespace userspace

void test02_01_04() {
    using userspace::M;
    M m;
    m.abstract_interface(4);
}


#include <iostream>
#include <type_traits>
#include <utility> // for std::forward_like

auto get_message() {
    return 42;
}

struct Scheduler {
    auto submit(auto&& m) {
        std::cout << std::boolalpha;
        std::cout << std::is_lvalue_reference<decltype(m)>::value << "\n";
        std::cout << std::is_rvalue_reference<decltype(m)>::value << "\n";
        return m;
    }
};

void test02_01_05() {
    Scheduler scheduler;
    auto callback = [m = get_message(), &scheduler](this auto&& self) -> bool {
        return scheduler.submit(std::forward_like<decltype(self)>(m));
    };
    callback(); // retry(callback)
    std::move(callback)(); // try-or-fail(rvalue)
}

struct S {
    int data_;

    // implicit this pointer
    int foo() {
        std::cout << __func__ << " ==6\n";
        return 6;
    }
    // int foo(this S); // Pass this by value
};

int test02_01_06() {
    S s{ 42 };
    return s.foo();
}

void test02_01() {
    test02_01_01();
    test02_01_02();
    test02_01_03();
    test02_01_04();
    test02_01_05();
    int n = test02_01_06();
}