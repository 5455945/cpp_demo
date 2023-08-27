#include "02-17.h"

// 17、特性十七：static operator()（P1169R4）
// 注意一下，maxsize是最大的可能大小，而op返回才是实际大小，因此逻辑的最后才有一个erase()操作，
// 用于删除多余的大小。这个特性在GCC 12，Clang 14，MSVC v19.31已经实现。

// 接着来看P2251，它更新了std::span和std::string_view的约束，从C++23开始，它们必须满足TriviallyCopyable Concept。
// 主流编译器都支持该特性。最后来看P0448，其引入了一个新的头文件。大家都知道，stringstream现在被广泛使用，
// 可以将数据存储到string或vector当中，但这些容器当数据增长时会发生「挪窝」的行为，若是不想产生这个开销呢？
// 提供了一种选择，你可以指定固定大小的buffer，它不会重新分配内存，但要小心数据超出buffer大小，
// 此时内存的所有权在程序员这边。一个小例子：

void test02_17() {

}
