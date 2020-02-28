//#include <iostream>
//#include <cassert>

// C++ 中的属性
// https://docs.microsoft.com/zh-cn/cpp/cpp/attributes?view=vs-2019

//void f2(bool b1, bool b2) {
//
//}
[[maybe_unused]] void f([[maybe_unused]] bool thing1,
    [[maybe_unused]] bool thing2)
{
    //[[maybe_unused]] bool b = thing1 && thing2;
    //assert(b); // 发行模式中，assert 在编译中被去掉，因而未使用 b
               // 无警告，因为它被声明为 [[maybe_unused]]
} // 未使用参数 thing1 与 thing2，无警告


// [[nodiscard]]可用于类声明、函数声明、枚举声明中，表示函数的返回值没有被接收，在编译时会出现警告。
struct [[nodiscard]] error_info{ };
error_info enable_missile_safety_mode() {
    return error_info{};
};
void launch_missiles() {};
void test_missiles() {
    enable_missile_safety_mode(); // 编译器可在舍弃 nodiscard 值时发布警告
    launch_missiles();
}
error_info& foo(error_info& ei) {
    return ei;
}

class [[nodiscard]] A {}; //该属性在这其实没用
enum class [[nodiscard]]  B {}; //该属性在这其实没用
class C {};

[[nodiscard]] int foo2()
{
    return 10;
}

[[nodiscard]] A func1() { return A(); }
[[nodiscard]] B func2() { return B(); }
[[nodiscard]] C func3() { return C(); }

void test_nodiscard()
{
    foo2();   //warning: ignoring return value
    func1();  //warning: ignoring return value
    func2();  //warning: ignoring return value
    func3();  //warning: ignoring return value
    A();      //warning: 
}

void f1() {
    error_info ei{};
    foo(ei); // 并非按值返回 nodiscard 类型，无警告
}

int main()
{
    f(true, true);
    //f2(true, true);
    f1();

    return 0;
}
