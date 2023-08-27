#include "02-24.h"

// 24、特性二十四：Literal suffixes for (signed) size_t（P0330R8）
// 这个特性为std::size_t类型加入了后缀uz，为signed std::size_t类型加入了后缀z。 
// 这个特性的作用是让我们在使用std::size_t类型时，可以更明确地指定它的类型。 下面是一个例子：

#include <vector>

void test02_24_01() {
    std::vector<int> v{ 0, 1, 2, 3 };

    // 以下 auto i = 0u, s = v.size, 在 vs2022 中报如下错误
    // C3538	在声明符列表中，“auto”必须始终推导为同一类型
    // E1594	对于此实体“auto”类型是 "size_t"，但之前默示为 "unsigned int"
    //for (auto i = 0u, s = v.size(); i < s; ++i) {
    //    /* use both i and v[i] */
    //}
}

// 这段代码在32位平台上可以编译通过，但是在64位平台上会出现错误。
// <source>(5) : error C3538 : in a declarator - list 'auto' must always deduce to the same type
// <source>(5) : note : could be 'unsigned int'
// < source > (5) : note : or 'unsigned __int64'

// 切地说，在32位平台上，std::vector::size_type被推导为unsigned int，而v.size()返回的类型为size_t。
// 而size_t在32位上为unsigned int，而在64位上为unsigned long long。 因此，当我们在32位平台上编译此代码时，
// i和v.size()的类型是相同的，都是unsigned int。

// 但是，当我们在64位平台上编译时，i和v.size()的类型不同，这就会导致错误。 通过为std::size_t增加后缀uz，
// 我们可以保证在任何平台上，std::size_t类型都被明确地指定为unsigned整数类型，从而避免上述问题。
// 同样，通过为signed std::size_t增加后缀z，我们可以保证在任何平台上，
// signed std::size_t类型都被明确地指定为带符号整数类型。

// 目前GCC 11和Clang 13已经支持了为std::size_t增加后缀uz、为signed std::size_t增加后缀z的特性。
// 这使得我们可以更加明确地指定std::size_t类型和signed std::size_t类型，
// 从而避免在不同平台上出现类型不匹配的问题。

void test02_24_02() {
    std::vector<int> v{ 0, 1, 2, 3 };
    //for (auto i = 0uz, s = v.size(); i < s; ++i) {
    //for (auto i = 0zu, s = v.size(); i < s; ++i) {
    //for (auto i = 0sz, s = v.size(); i < s; ++i) {
    for (auto i = 0ull, s = v.size(); i < s; ++i) {
        /* use both i and v[i] */
    }
}


void test02_24() {
    test02_24_01();
    test02_24_02();
}
