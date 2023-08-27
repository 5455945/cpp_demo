#include "02-14.h"

#include <iostream>

// 14、特性十四：#warning（P2437）
// #warning是一项主流编译器都支持的特性，它已经被C23和C++23收录。 
// 这个小特性可以用来产生警告信息，与#error不同，它并不会停止翻译。 使用起来非常简单：

void test02_14_01() {
  std::cout << __func__ << " in\n";
#ifndef FOO
	//#warning "FOO defined, performance might be limited"
	// C1021	无效的预处理器命令“warning”

#endif
  std::cout << __func__ << " out\n";
}

// 目前MSVC不支持该特性，其他主流编译器都支持。


void test02_14() {
	test02_14_01();
}
