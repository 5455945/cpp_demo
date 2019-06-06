#include "AppendixA.h"

namespace {
    // 具有平凡默认构造函数的类
    class CX
    {
    private:
        int a;
        int b;
    public:
        CX() = default;
        CX(int a_, int b_) :
            a(a_), b(b_)
        {}
        int get_a() const
        {
            return a;
        }
        int get_b() const
        {
            return b;
        }
        int foo() const
        {
            return a + b;
        }
    };
}
void AppendixA_03() {
    CX cx1;
    CX cx2(1, 2);
    int a11 = cx1.get_a();
    int b11 = cx1.get_b();
    int c10 = cx1.foo();
    int a21 = cx2.get_a();
    int b21 = cx2.get_b();
    int c20 = cx2.foo();
}
