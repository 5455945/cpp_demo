#include "Concurrency05.h" 
#include <iostream>
// 5.3.1 synchronizes-with��ϵ
// 5.3.2 happens-before��ϵ
namespace {
    // һ���������õĲ����Ĺ���˳����δ�����
    void foo(int a, int b)
    {
        std::cout << a << ", " << b << std::endl;
    }
    int get_num()
    {
        static int i = 0;
        return ++i;
    }
}
void Concurrency05_03() {
    foo(get_num(), get_num()); // ��get_num()�ĵ����������
}