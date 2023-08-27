#include "02-11.h"

// 11、特性十一：Narrowing contextual conversions to bool（P1401R5）

// 这个提案允许在static_assert和if constexpr中从整形转换为布尔类型。
// 以下表格就可以表示所有内容。

/*
| Before | After |
| -------------------------------------- - | -------------------------------- - |
| if constexpr (bool(flags & Flags::Exec)) | if constexpr (flags & Flags::Exec) |
| if constexpr (flags & Flags::Exec != 0) | if constexpr (flags & Flags::Exec) |
| static_assert(N % 4 != 0); | static_assert(N % 4); |
| static_assert(bool(N)); | static_assert(N); |
*/

// 在严格的C++编译器中，以前在这种情境下，int类型无法自动转换为bool类型，需要手动进行强制转换。
// 但是，在C++23中，这种情况得到了改善。 目前，GCC 9和Clang 13以上版本已经支持了这个特性。


void test02_11() {

}
