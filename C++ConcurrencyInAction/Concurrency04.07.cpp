#include "Concurrency04.h" 
#include <string>
#include <future>
#include <iostream>
// 使用std::async来将参数传递给函数
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

    //X baz(&x);
    //auto f6 = std::async(std::launch::async, Y(), 1.2); // 在新线程中运行
    //auto f7 = std::async(std::launch::deferred, baz, std::ref(x));
    //auto f8 = std::async(std::launch::async | std::launch::deferred,
    //    baz, std::ref(x));
    //auto f9 = std::async(baz, std::ref(x));
    //f7.wait();
}