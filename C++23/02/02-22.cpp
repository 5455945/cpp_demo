#include "02-22.h"

#include <algorithm> // std::clamp
#include <cmath> // std::isfinite

// 22�����Զ�ʮ����Attributes��P1774R8, P2173R1, P2156R1��
// ��C++23�У�AttributesҲ��һЩ�ı䡣
// ���ȣ�P1774������һ���µ�Attribute [[assume]] ��ʵ���ϣ������������У����Ƶ������Ѿ����ڣ�
// ����MSVC��ICCʹ��__assume()��Clangʹ��__builtin_assume()������GCCû�����Ƶ����ԣ�
// �����������ʵ�ֱ�׼ [[assume]] �ı�����֮һ��Ŀǰ��ֻ��GCC 13֧�ָ����ԣ��ð汾Ԥ�������·�����ͬʱҲ��Rangs��֧�ַǳ����ơ�
// ���ڣ����ǿ���ͨ������ʹ�� [[assume]] ��


#if defined(__clang__)
#define ASSUME(expr) __builtin_assume(expr)
#elif defined(__GNUC__) && !defined(__ICC)
#define ASSUME(expr) if (expr) {} else { __builtin_unreachable(); }
#elif defined(_MSC_VER) || defined(__ICC)
#define ASSUME(expr) __assume(expr)
#endif


// ���ĵ��е�һ�����ӣ�

void limiter(float* data, size_t size) {
    ASSUME(size > 0);
    ASSUME(size % 32 == 0);

    for (size_t i = 0; i < size; ++i) {
        ASSUME(std::isfinite(data[i]));
        data[i] = std::clamp(data[i], -1.0f, 1.0f);
    }
}

void test02_22_01() {
    float data[] = { 2.0f, 2.0f, 3.5f, 4.8f, 6.9f };
    limiter(data, 5);
}
// ��һ���Ǽ���size����Ϊ0�������������ڶ������߱�����size����32�ı������������������ݲ���NaN������С����
// ��Щ���費�ᱻ�������飬���������������Ϊ�棬�������������Ż����롣
// ��Ҫע����ǣ������Щ����Ϊ�٣����ܻ����δ������Ϊ��UB����

// ������ʹ��[[assume]]���ԺͲ�ʹ�ø����Ա��������ָ�����ԱȽ����


// ���⣬P2173ʹ�ÿ�����Lambda���ʽ��ʹ��Attributes��������һ�����ӣ�
// Any attribute so specified does not appertain to the function 
// call operator or operator template itself, but its type.
//auto lam = [] [[nodiscard]] () ->int { return 42; };

void test02_22_02()
{
    //lam();
}

// Output:
// <source>: In function 'int main()':
// <source>:12:8: warning: ignoring return value of '<lambda()>', declared with attribute 'nodiscard' [-Wunused-result]
//    12 |     lam();
//       |     ~~~^~
// <source>:8:12: note: declared here
//     8 | auto lam = [][[nodiscard]] ->int { return 42; };
//       |            ^


// ��Ҫע����ǣ�Attributes���ڱհ����ͣ�closure type������������operator()��
// ��ˣ���ЩAttributes����ʹ�ã����� [[noreturn]] �������������Ŀ��������᷵�ص����÷���
// ������Lambda�����ǻ᷵�صġ� ����֮�⣬���ﻹչʾ��C++����һ��Lambda���ԡ� ��C++23֮ǰ��
// ��򵥵�Lambda���ʽΪ{}��������C++23������[]{}������ʡ���޲�ʱ�����ţ���Ҫ�鹦��P1102�� 
// ����GCC 9�о��Ѿ�֧����Lambda���ʽ��ʹ��Attributes����Clang 13����Ҳ֧�ָ����ԡ�
// ���P2156�Ƴ��˶��ظ�Attributes�����ơ������֮�������ظ�Attributes���﷨���в�һ�¡�������һ�����ӣ�

//// Not allow
//[[nodiscard, nodiscard]] auto foo() {
//    return 42;
//}

// Allowed
[[nodiscard]] [[nodiscard]] auto foo() {
    return 42;
}

// Ϊ�˱�֤��׼���Ӽ򵥺�һ�£�P2156�Ƴ��˶��ظ�Attributes�����ơ� ��ʲô����»�����ظ�Attributes�����Կ�һ�������еĽ��ͣ�

// During this discussion, it was brought up that the duplication across attribute-specifiers are 
// to support cases where macros are used to conditionally add attributes to an attribute-specifier-seq, 
// however it is rare for macros to be used to generate attributes within the same attribute-list. 
// Thus, removing the limitation for that reason is unnecessary.

// ��ʹ�ú�����ʱ�����ܻ�����ظ���Attributes���������ʹ�õڶ����﷨��ʵ���ϣ������ں����ɵĴ������ʹ�õ�һ���﷨��
// �����Ϊʲô��׼�������������ԭ�򡣵��ǣ��������Ʋ�û���ñ�׼���򵥡���ˣ������Ƴ��˸����ơ� 
// Ŀǰ��ʹ��GCC 11��Clang 13+���������﷨�Ľ��������һ�¡�


void test02_22() {
    test02_22_01();
    test02_22_02();
}
