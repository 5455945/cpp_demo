#include "co_vs_callback.h"
#include "co_vs_await.h"
#include "co_vs_return.h"
#include "co_vs_yield.h"

int main(int argc, char** argv) {
    co_vs_callback();
    co_vs_await();
    co_vs_return();
    co_vs_yield();

    return 0;
}

// 参考文档
// 01 C++ coroutine
// https://www.cnblogs.com/heishanlaoy/p/11760368.html

// 02 协程原理解析(1)
// https://zhuanlan.zhihu.com/p/52061644

// 03 https://github.com/franktea/temp/blob/master/uncategorized/coroutine.md

// 04 C++ 协程介绍[译]
// https://blog.csdn.net/zhangpeterx/article/details/100138656

// 05 C++协程
// https://blog.csdn.net/eunice_fan1207/article/details/91894192

// 06 万字长文 | 漫谈libco协程设计及实现
// https://cloud.tencent.com/developer/article/1459729
