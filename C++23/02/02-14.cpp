#include "02-14.h"

#include <iostream>

// 14������ʮ�ģ�#warning��P2437��
// #warning��һ��������������֧�ֵ����ԣ����Ѿ���C23��C++23��¼�� 
// ���С���Կ�����������������Ϣ����#error��ͬ����������ֹͣ���롣 ʹ�������ǳ��򵥣�

void test02_14_01() {
  std::cout << __func__ << " in\n";
#ifndef FOO
	//#warning "FOO defined, performance might be limited"
	// C1021	��Ч��Ԥ���������warning��

#endif
  std::cout << __func__ << " out\n";
}

// ĿǰMSVC��֧�ָ����ԣ�����������������֧�֡�


void test02_14() {
	test02_14_01();
}
