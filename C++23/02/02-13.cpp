#include "02-13.h"

#include <iostream>

// 13、特性十三：#elifdef and #elifndef（P2334）
// C23中加入了这两个预处理指令，它们来源于C工作组（WG14），为了兼容C，C++23也将它们加入了。 
// #ifdef和#ifndef分别是#if defined()和#if !defined()的简写，而#elif defined()和#elif !defined()却并没有与之对应的简写指令。
// 因此，C23引入了#elifdef和#elifndef来弥补这一缺陷。总之，这是两个非常简单的小特性，目前已被GCC 12和Clang 13支持。

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
