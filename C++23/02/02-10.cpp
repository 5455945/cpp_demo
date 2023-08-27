#include "02-10.h"

#include <print>
#include <vector>

// 10������ʮ��auto(x) decay copy��P0849��
// C++23�е�����᰸Ϊauto�ؼ��������������µ��﷨����auto(x)��auto { x }�����ǵ�������ͬ������Ϊx����һ�ݿ����� 
// Ϊʲô��Ҫ�������﷨�أ����ǿ��Կ�һ�����ӣ�

void bar(const auto& param) {
    std::println("{}", param);
}

void foo(const auto& param) {
    auto copy = param;
    bar(copy);
}

// ����������һ������foo()�������е��ú���bar()����ϣ����bar()���ݲ���param��һ�ݿ���������������£�
// ����ͨ����Ҫ��������һ����ʱ���������߲������·�ʽ��
void foo1(const auto& param) {
    bar(std::decay_t<decltype(param)>{param});
}

// Ȼ����ʹ�����ַ�ʽ��Ҫ�ֶ�ȥ����������Σ�ֻ��������T������������鷳�� 
// �������auto(x)�﷨���൱�����õ�decay copy������ֱ������д��
void foo2(const auto& param) {
    //bar(auto{ param });
}

void test02_10_01() {
    foo("hello world");
    foo1("hello world");
    foo2("hello world");
}

// Ҳ����Щ�˻�û����ʶ�������﷨�ı�Ҫ�ԣ�������������һЩ���Ӹ��ӵ����ӣ��������᰸�ĵ���
void pop_front_alike(auto& container) {
    std::erase(container, container.front());
}

void test02_10_02() {
    std::vector fruits{ "apple", "apple", "cherry", "grape",
        "apple", "papaya", "plum", "papaya", "cherry", "apple" };
    pop_front_alike(fruits);

    // msvc ��ʱ���벻��
    //std::print("{}\n", fruits);
}
// Output:
// ["cherry", "grape", "apple", "papaya", "plum", "papaya", "apple"]

// ��Ҫע����ǣ���������ĳ�������Ƿ����Ԥ�ڡ������û�з������⣬���������ٴ���������
// pop_front_alike()�������Ƴ��������������һ��Ԫ����ͬ��Ԫ�ء� ��ˣ�����Ľ��Ӧ���ǣ�
// ["cherry", "grape", "papaya", "plum", "papaya", "cherry"]

// ��ô��������������أ���������һ��gcc��std::erase()��ʵ�֣�

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

// ʵ���ϣ�std::remove()�������յ��õ���remove_if()�㷨������ͳ�������㷨�С����㷨ÿ�ζ���Ƚϵ�ǰԪ�غ����Ƴ�Ԫ�أ�
// ������ǲ���ȣ�����õ�ǰԪ�ظ��ǵ�ǰ__result��������ֵ��Ȼ��__result����ƶ�һλ��ͨ�������ظ����������
// ������ЧԪ�����ն����ܵ�__result��������ǰ�档
// �������ڣ����Ƴ�Ԫ��ʼ��ָ���׸�Ԫ�أ�������������Ϊconst T& �������������Ԫ�ظ��ǲ������ı䡣
// Ϊ�˵õ���ȷ�Ľ������Ҫ���¸���һ��ֵ��
// ��ˣ�����С�Ĵ�����ľͿ��Եõ���ȷ�Ľ����

void pop_front_alike2(auto& container) {
    auto copy = container.front();
    std::erase(container, copy);
}

// Ȼ�������ַ�ʽ�ǳ���ֱ����һ������£�������д��Ӧ���ǵȼ۵ġ�Ϊ�˸��õر��Ч�������ǿ��Խ����Ʋ�������Ϊһ�������ĺ�����
auto copy(const auto& value) {
    return value;
}

void pop_front_alike3(auto& container) {
    std::erase(container, copy(container.front()));
}

// ʵ���ϣ�auto{ x }��auto(x)���൱��copy()������ֻ�������������õ������еġ�

void test02_10() {
    test02_10_01();
    test02_10_02();
}