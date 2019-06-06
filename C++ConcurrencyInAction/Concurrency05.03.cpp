#include "Concurrency05.h" 
#include <iostream>
// 5.3.1 synchronizes-with��ϵ
// 5.3.2 happens-before��ϵ
namespace {
    // һ���������õĲ����Ĺ���˳����δ�����
    void foo(int num, int a, int b)
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
    //foo(0, get_num(), get_num()); // ��get_num()�ĵ����������
    // ���ڲ�ͬ�ı�����ʵ�֣������ǹ̶���
    for (int i = 0; i < 100; i++) {
        foo(i, get_num(), get_num());
    }
}