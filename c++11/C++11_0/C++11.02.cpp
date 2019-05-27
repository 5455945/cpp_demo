#include "C++11.02.h"
#include <iostream>
#include <string>
using namespace std;

// �ڶ��� ��֤�ȶ��Ժͼ�����

// 2.1 ������C99�ļ�����
// C99�е�Ԥ�����
// 2.1.1 __func__Ԥ�����ʶ��
// 2.1.2 _Pragma ������
// 2.1.3 ���������궨�� �� __VA_ARGS__
// 2.1.4 ��խ�ַ�������

// �����嵥2-1
void Test_2_1() {
    //std::cout << "standard clib: " << __STDC_HOSTED__ << std::endl;
    //std::cout << "standard c: " << __STDC__ << std::endl;
    //std::cout << "c standard version: " << __STDC_VERSION__ << std::endl;
    //std::cout << "sio/iec: " << STDC_SIO_10646__ << std::endl;
}

// �����嵥2-2
// ��vs2013�У�__func__��δ�����ı�ʶ��
//const char* hello2015() { return __func__; }
//const char* world2015() { return __func__; }
const char* hello() { return __FUNCTION__; }
const char* world() { return __FUNCTION__; }
void Test_2_2() {
    cout << hello() << ", " << world() << endl;
}

// �����嵥2-3
struct TestStruct {
    TestStruct() : name(__FUNCTION__) {};
    const char* name;
};
void Test_2_3() {
    TestStruct ts;
    cout << ts.name << endl;
}

//// ��Ϊ����������Ĭ��ֵ�ǲ������
//void FuncFail(string func_name = __FUNCTION__) {};
//void FuncFail2015(string func_name = __func__) {};

// 2.2 longlong ����

// 2.3 ��չ������

// 2.4 __cplusplus

// 2.5 ��̬���� static_assert

// 2.6 noexcept���η���noexcept������

// 2.7 ���ٳ�ʼ����Ա����

// 2.8 �Ǿ�̬��Ա��sizeof

// 2.9 ��չ��friend�﷨

// 2.10 final / override

// 2.11 ģ�庯����Ĭ��ģ�����

// 2.12 �ⲿģ��

// 2.13 �ֲ�������������ģ�����

// 


void Test_C11_02() {
    Test_2_1();
    Test_2_2();
    Test_2_3();
    int n = 5;
}
