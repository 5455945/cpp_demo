#include <cassert>
#include <memory>

// https://zh.cppreference.com/w/cpp/memory/to_address
// https://zh.cppreference.com/w/cpp/memory/pointer_traits/to_address
//// 可能实现
//template<class T>
//constexpr T* to_address(T* p) noexcept
//{
//    static_assert(!std::is_function_v<T>);
//    return p;
//}
//
//template<class T>
//constexpr auto to_address(const T& p) noexcept
//{
//    if constexpr (requires{ std::pointer_traits<T>::to_address(p); }) {
//        return std::pointer_traits<T>::to_address(p);
//    }
//    else {
//        return std::to_address(p.operator->());
//    }
//}

template<class A>
auto allocator_new(A& a)
{
    auto p = a.allocate(1);
    try {
        std::allocator_traits<A>::construct(a, std::to_address(p));
    }
    catch (...) {
        a.deallocate(p, 1);
        throw;
    }
    return p;
}

template<class A>
void allocator_delete(A& a, typename std::allocator_traits<A>::pointer p)
{
    std::allocator_traits<A>::destroy(a, std::to_address(p));
    a.deallocate(p, 1);
}

void test_to_address01() {
    std::allocator<int> a;
    auto p = allocator_new(a);
    allocator_delete(a, p);
}

// https://github.com/glenfe/to_address/blob/master/test/to_address_test.cpp
// https://zh.cppreference.com/w/cpp/memory/pointer_traits/to_address
template<class T>
class P1 {
public:
    explicit P1(T* p)
        : p_(p) { }

    T* operator->() const noexcept {
        return p_;
    }

private:
    T* p_;
};

template<class T>
class P2 {
public:
    explicit P2(T* p)
        : p_(p) { }

    P1<T> operator->() const noexcept {
        return p_;
    }

private:
    P1<T> p_;
};

template<class T>
class P3 {
public:
    explicit P3(T* p)
        : p_(p) { }

    T* get() const noexcept {
        return p_;
    }

private:
    T* p_;
};

namespace std {

    template<class T>
    struct pointer_traits<P3<T> > {
        static T* to_address(const P3<T>& p) noexcept {
            return p.get();
        }
    };
} // std

template<class T>
class P4 {
public:
    explicit P4(T* p)
        : p_(p) { }

    T* operator->() const noexcept {
        return nullptr;
    }

    T* get() const noexcept {
        return p_;
    }

private:
    int* p_;
};

namespace std {

    template<class T>
    struct pointer_traits<P4<T> > {
        static T* to_address(const P4<T>& p) noexcept {
            return p.get();
        }
    };

} // std

void test_to_address02() {
    int i = 0;
    assert(std::to_address(&i) == &i);
    int* p = &i;
    assert(std::to_address(p) == &i);
    P1<int> p1(&i);
    assert(std::to_address(p1) == &i);
    P2<int> p2(&i);
    assert(std::to_address(p2) == &i);
    P3<int> p3(&i);
    assert(std::to_address(p3) == &i);
    P4<int> p4(&i);
    assert(std::to_address(p4) == &i);
}

// https://zh.cppreference.com/w/cpp/types/remove_cvref
#include <iostream>
#include <type_traits>
void test_remove_cvref() {
    std::cout << std::boolalpha
        << std::is_same_v<std::remove_cvref_t<int>, int> << '\n'
        << std::is_same_v<std::remove_cvref_t<int&>, int> << '\n'
        << std::is_same_v<std::remove_cvref_t<int&&>, int> << '\n'
        << std::is_same_v<std::remove_cvref_t<const int&>, int> << '\n'
        << std::is_same_v<std::remove_cvref_t<const int[2]>, int[2]> << '\n'
        << std::is_same_v<std::remove_cvref_t<const int(&)[2]>, int[2]> << '\n'
        << std::is_same_v<std::remove_cvref_t<int(int)>, int(int)> << '\n';
}

// https://zh.cppreference.com/w/cpp/utility/functional/bind_front
#include <functional>
#include <iostream>
int minus(int a, int b) {
    return a - b;
}
void test_bind_front() {
    auto fifty_minus = std::bind_front(&minus, 50);
    std::cout << fifty_minus(3);
}

int main()
{
    test_to_address01();
    test_to_address02();
    test_remove_cvref();
    test_bind_front();
    return 0;
}
