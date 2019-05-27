#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <cstdio>
#include <atomic>
#include <thread>
#include <map>
#include "C++11.02.h"
#include "C++11.03.h"
#include "C++11.04.h"
#include "C++11.05.h"
#include "C++11.06.h"
#include "C++11.07.h"

#if __cplusplus < 199711L
//#if __cplusplus < 201103L
#error "��ʹ��֧��C++11�ı�����"
#endif

// C++11���¹ؼ���
// alignas
// 

// vs2013��֧��noexcept
//void TestNoExcept() noexcept{
//    return ;
//}
#define CONCAT(x)  PRAGMA(test on #x)
#define PRAGMA(x) __pragma(#x)
#define log(...) printf(__VA_ARGS__);

using namespace std;

atomic_llong g_reulst{ 0 };

int main(int argc, char** argv) {
    // ���ͱ���
    using si = int;
    si n = 5;
    std::cout << n << std::endl;

    // �����ռ����
    namespace newname = std;
    newname::cout << n << newname::endl;

    // ��ָ�����ͣ�ȡ��NULL�������Ķ�����
    const int *pNULL = nullptr;

    //constexpr ���ڶ������ʱ�ɼ���ĳ������ʽ��
    // 1������ʱ�������������������Կ��Լ���ú�����ֵ������һЩ�꣨macro���������Ϳ����� constexpr ���������õĴ��档
    // 2������ʱ�������ݣ�����ĳЩ�������ģ���ж���ľ�̬�������ݣ���ǰ���� static const ���壬
    // ���ڿ��Ը��� constexpr �����ˣ����Ի�ø��õ�Ч�ʺͰ�ȫ�ԡ�
    // VS2013��֧��
    // constexpr int *q = nullptr;

    // ���������ʼ��
    std::vector<int> ivec = { 1, 2, 3, 4 };
    std::vector<std::string> svec = { "red", "green", "blue" };

    // auto
    auto adder = [](int op1, int op2) { return op1 + op2; };
    auto adder1 = [](std::string op1, std::string op2) { return op1 + op2; };

    // vs2013��֧�ֲ����Ƶ�
    // auto adder = [](auto op1, auto op2){ return op1 + op2; };

    std::cout << "int result : "
        << std::accumulate(ivec.begin(),
            ivec.end(),
            0,
            adder)
        << "\n";
    std::cout << "string result : "
        << std::accumulate(svec.begin(),
            svec.end(),
            std::string(""),
            adder1)
        << "\n";

    //std::cout << __func__ << std::endl;
    std::cout << __FUNCTION__ << std::endl;
    //__pragma(12345);
    log("log: %s %d %s\n", __FUNCTION__, __LINE__, __FILE__);

    std::wstring wstr = L"���a";
    std::string str = "ttttt";

    int i = 7;
    printf_s("i = 7 i++ = %d", i++);

    //static_assert(__cplusplus >= 201103L, "����ʹ��֧��C++11�ı���������֧�ָô���");
    Test_C11_02();
    Test_C11_03();
    Test_C11_04();
    Test_C11_05();
    Test_C11_06();
    Test_C11_07();
    return 0;
}
