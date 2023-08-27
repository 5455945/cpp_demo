#include "02-08.h"

//  8�����԰ˣ�import std��P2465��
//  C++20ģ���ʹ�ô���һ���Ѷȣ���Ҳ����Ϊ��׼����û���ṩģ���ʵ�֡�
// ��ˣ�������Եļ��������Ȼ���ơ� ���ڣ����ǿ��Ա�д���´��룺

// This will set the VS configuration property C/C++->Language->C++ Language Standard to /std:c++latest. 
// Visual Studio 17.6 now also provides a property C/C++->Language->Build ISO C++23 Standard Library Modules which by default is set to Yes 
// and will automatically build the standard library modules on /std:c++latest as part of your project build. 
// So no special handling is required anymore.
// 
// [����]==>[C/C++]==>[����]==>[���� ISO C++23 ��׼��ģ��]=��

import std;

void test02_08_01() {
    std::print("Hello standard library modules!\n");
}

// //���������ܶԱȣ�
// 
// ```
// || #include needed headers | Import needed headers | import std | #include all headers | Import allheaders|
// |:--| : --| : --| : --| : --| : --|
// |"Hello world"(<iostream>) | 0.87s | 0.32s | 0.08s | 3.42s | 0.62s|
// |"Mix"(9 headers) | 0.20s | 0.77s | 0.44s | 3.53s | 0.99s |
// ```
// ���������ʹ�û�ϵ�C��C++���룬��ô����ʹ��std.compatģ�飬��ģ�齫�������е�C�����ͱ�׼�⺯����
// Ŀǰ�������Լ���û�еõ���������֧�֡�

void test02_08() {
    test02_08_01();
}