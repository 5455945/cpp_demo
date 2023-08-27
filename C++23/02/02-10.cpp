#include "02-10.h"

#include <print>
#include <vector>

// 10、特性十：auto(x) decay copy（P0849）
// C++23中的这个提案为auto关键字引入了两个新的语法，即auto(x)和auto { x }，它们的作用相同，都是为x创建一份拷贝。 
// 为什么需要这样的语法呢？我们可以看一个例子：

void bar(const auto& param) {
    std::println("{}", param);
}

void foo(const auto& param) {
    auto copy = param;
    bar(copy);
}

// 假设我们有一个函数foo()，在其中调用函数bar()，并希望向bar()传递参数param的一份拷贝。在这种情况下，
// 我们通常需要额外声明一个临时变量，或者采用以下方式：
void foo1(const auto& param) {
    bar(std::decay_t<decltype(param)>{param});
}

// 然而，使用这种方式需要手动去除多余的修饰，只留下类型T，这样会更加麻烦。 
// 而引入的auto(x)语法则相当于内置的decay copy，可以直接这样写：
void foo2(const auto& param) {
    //bar(auto{ param });
}

void test02_10_01() {
    foo("hello world");
    foo1("hello world");
    foo2("hello world");
}

// 也许有些人还没有意识到这种语法的必要性，下面我们来看一些更加复杂的例子，来自于提案文档。
void pop_front_alike(auto& container) {
    std::erase(container, container.front());
}

void test02_10_02() {
    std::vector fruits{ "apple", "apple", "cherry", "grape",
        "apple", "papaya", "plum", "papaya", "cherry", "apple" };
    pop_front_alike(fruits);

    // msvc 暂时编译不过
    //std::print("{}\n", fruits);
}
// Output:
// ["cherry", "grape", "apple", "papaya", "plum", "papaya", "apple"]

// 需要注意的是，下面给出的程序输出是否符合预期。如果您没有发现问题，请允许我再次提醒您：
// pop_front_alike()函数将移除容器中所有与第一个元素相同的元素。 因此，理想的结果应该是：
// ["cherry", "grape", "papaya", "plum", "papaya", "cherry"]

// 那么，问题出在哪里呢？我们来看一下gcc中std::erase()的实现：

/*
template<typename _ForwardIterator, typename _Predicate>
_ForwardIterator
__remove_if(_ForwardIterator __first, _ForwardIterator __last,
    _Predicate __pred)
{
    __first = std::__find_if(__first, __last, __pred);
    if (__first == __last)
        return __first;
    _ForwardIterator __result = __first;
    ++__first;
    for (; __first != __last; ++__first)
        if (!__pred(__first)) {
            *__result = _GLIBCXX_MOVE(*__first);
            ++__result;
        }

    return __result;
}


template<typename _Tp, typename _Alloc, typename _Up>
inline typename vector<_Tp, _Alloc>::size_type
erase(vector<_Tp, _Alloc>& __cont, const _Up& __value)
{
    const auto __osz = __cont.size();
    __cont.erase(std::remove(__cont.begin(), __cont.end(), __value),
        __cont.end());
    return __osz - __cont.size();
}
*/

// 实际上，std::remove()函数最终调用的是remove_if()算法，问题就出在这个算法中。该算法每次都会比较当前元素和欲移除元素，
// 如果它们不相等，则会用当前元素覆盖当前__result迭代器的值，然后__result向后移动一位。通过不断重复这个操作，
// 所有有效元素最终都会跑到__result迭代器的前面。
// 问题在于，欲移除元素始终指向首个元素，并且它的类型为const T& ，因此它会随着元素覆盖操作而改变。
// 为了得到正确的结果，需要重新复制一份值。
// 因此，做出小的代码更改就可以得到正确的结果。

void pop_front_alike2(auto& container) {
    auto copy = container.front();
    std::erase(container, copy);
}

// 然而，这种方式非常反直觉，一般情况下，这两种写法应该是等价的。为了更好地表达效果，我们可以将复制操作定义为一个单独的函数。
auto copy(const auto& value) {
    return value;
}

void pop_front_alike3(auto& container) {
    std::erase(container, copy(container.front()));
}

// 实际上，auto{ x }和auto(x)就相当于copy()函数，只不过它们是内置到语言中的。

void test02_10() {
    test02_10_01();
    test02_10_02();
}