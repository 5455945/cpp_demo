#include "02-13.h"

#include <iostream>

// 13������ʮ����#elifdef and #elifndef��P2334��
// C23�м�����������Ԥ����ָ�������Դ��C�����飨WG14����Ϊ�˼���C��C++23Ҳ�����Ǽ����ˡ� 
// #ifdef��#ifndef�ֱ���#if defined()��#if !defined()�ļ�д����#elif defined()��#elif !defined()ȴ��û����֮��Ӧ�ļ�дָ�
// ��ˣ�C23������#elifdef��#elifndef���ֲ���һȱ�ݡ���֮�����������ǳ��򵥵�С���ԣ�Ŀǰ�ѱ�GCC 12��Clang 13֧�֡�

void test02_13() {

#ifdef __TEST02_13
	std::cout << __func__ << __LINE__ << std::endl;
#elifdef __TEST02_14
   std::cout << __func__ << __LINE__ << std::endl;
#else
	std::cout << __func__ << __LINE__ << std::endl;
#endif

#define __TEST02_13_2 

#ifndef __TEST02_13_2
	std::cout << __func__ << __LINE__ << std::endl;
#elifndef __TEST02_14_2
  std::cout << __func__ << __LINE__ << std::endl;
#else
	std::cout << __func__ << __LINE__ << std::endl;
#endif


}
