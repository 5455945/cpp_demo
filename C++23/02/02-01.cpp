#include "02-01.h"

// 1������һ��Deducing this
// Deducing this��C++23������Ҫ������֮һ������2022��03�·ݱ�msvc֧�֣�������v19.32�汾֮��ʹ�á�
// ��Ա��������һ����ʽ������������ڷǾ�̬��Ա�����������ʽ�����������ָ������thisָ�롣
// �����ھ�̬��Ա�����������ʽ�������������Ϊ����ƥ���κβ������������Ϊ�˱�֤���ؾ�������������С�
// Deducing this���������������ṩ��һ�ֽ��Ǿ�̬��Ա�����ġ���ʽ�����������Ϊ����ʽ����������ķ�����
// Ϊʲôֻ��ԷǾ�̬��Ա�����أ���Ϊ��̬��Ա������û��thisָ�룬��ʽ������������ܺ�thisָ�뻮�Ⱥţ�
// ��̬����ӵ����ʽ�������ֻ�Ǳ�֤���ؾ����ܹ��������ж��ѣ��������û�������ô���


// ͨ��Deducing this�����ǿ��Խ���ʽ���������ʽ��д�������﷨Ϊthis+type��
struct S_implicit0 {
    void foo() {}
};

struct S_explicit1 {
    void foo(this S_explicit1&) {}
};


// ����᰸�ĸ���������������Ա�������������������ࡣ�ٸ����ӣ�
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

// ʹ��Deducing this����������ҪΪͬһ����Ա������д���ְ汾�����Σ�����&, const&, &&, const&& �ȣ�
// ��Ϊ���ǵ��߼���û��̫��ı仯����ȫ���ظ��Ļ�еʽ������
// ���ڣ���ֻ��Ҫ��дһ���汾���ɡ� ������˵�����ǿ���ʹ��ģ����ʽ�Ĳ�����
// ͨ������ʹ��Self��Ϊ��ʽ������������ƣ��ⲻ������˼�壬�������������Ա���һ���ԡ� 
// ����֮�⣬Deducing this�������������ʹ�ó�����ͬʱҲ��һ���µĶ��Ƶ��ʾ��ʽ��
// ���磬����Deducing this����ʵ�ֵݹ�Lambdas��

#include <iostream> // std::cout
void test02_01_02() {
    auto gcd = [](this auto self, int a, int b) -> int {
        return b == 0 ? a : self(b, a % b);
    };

    std::cout << gcd(20, 30) << "\n";
}


//����Deducing this��Lambda�����õ�����ǿ���ڹ�ȥ���ݹ�Lambdas����ʵ�֣�����ʹ��Deducing this�������ɵ�ʵ����һ�㡣

// ���⣬Deducing this�����Լ�CRTP��Curiously Recurring Template Pattern����CRTPͨ������C++�еľ�̬��̬�ԣ�
// ������Ҫ��������̳�һ��ģ����ಢ��������Ϊģ��������ݡ�ͨ��ʹ��Deducing this��
// ��ģ������в�����Ҫ��ʽָ�����������ͣ����ǿ���ͨ���ƶ�thisָ�����Ƶ������������͡�
// ��ʹ��CRTP������Ӽ���������⡣
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

// ���������µķ�ʽʵ��CRTP���ܹ�ʡȥCR��T��ʹ�ô��������Ȼ�����������⣬��Ҳ��һ��ȫ�µĶ��Ƶ㷽ʽ������Ϊ�򵥵����ӣ�
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