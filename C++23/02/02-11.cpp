#include "02-11.h"

// 11������ʮһ��Narrowing contextual conversions to bool��P1401R5��

// ����᰸������static_assert��if constexpr�д�����ת��Ϊ�������͡�
// ���±��Ϳ��Ա�ʾ�������ݡ�

/*
| Before | After |
| -------------------------------------- - | -------------------------------- - |
| if constexpr (bool(flags & Flags::Exec)) | if constexpr (flags & Flags::Exec) |
| if constexpr (flags & Flags::Exec != 0) | if constexpr (flags & Flags::Exec) |
| static_assert(N % 4 != 0); | static_assert(N % 4); |
| static_assert(bool(N)); | static_assert(N); |
*/

// ���ϸ��C++�������У���ǰ�������龳�£�int�����޷��Զ�ת��Ϊbool���ͣ���Ҫ�ֶ�����ǿ��ת����
// ���ǣ���C++23�У���������õ��˸��ơ� Ŀǰ��GCC 9��Clang 13���ϰ汾�Ѿ�֧����������ԡ�


void test02_11() {

}
