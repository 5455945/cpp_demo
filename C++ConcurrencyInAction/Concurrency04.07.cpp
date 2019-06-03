#include "Concurrency04.h" 
#include <string>
#include <future>
#include <iostream>
namespace {

}
void Concurrency04_07() {
    struct X
    {
        void foo(int, std::string const& rhs) { std::cout << rhs << std::endl; };
        std::string bar(std::string const& rhs) { return ""; };
    };
    X x;
    auto f1 = std::async(&X::foo, &x, 42, "hello");
    auto f2 = std::async(&X::bar, x, "goodbye");

    struct Y
    {
        double operator()(double a) { return a; };
    };
    Y y;
    auto f3 = std::async(Y(), 3.141);
    auto f4 = std::async(std::ref(y), 2.718);
    //X baz(X&);
    //auto f6 = std::async(baz, std::ref(x));
    class move_only
    {
    public:
        move_only() {};
        move_only(move_only&&) {};
        move_only(move_only const&) = delete;
        move_only& operator=(move_only&& rhs) { return rhs; };
        move_only& operator=(move_only const&) = delete;
        void operator()() {};
    };
    auto f5 = std::async(move_only());
}