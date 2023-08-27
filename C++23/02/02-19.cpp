#include "02-19.h"

#include <type_traits> // std::underlying_type_t
#include <print> // std::print

// 19������ʮ�ţ�std::to_underlying��P1682R3��
// ͬ��������ͷ�ļ����ҵ�����std::type_identity�������������Ƶ���ĳ�����ʽ��Ǳ�����ͣ��൱�����´�����﷨�ǣ�
// static_cast<std::underlying_type_t<Enum>>(e);
// �ٸ��򵥵İ�����

void print_day(int a) {
    std::print("{}\n", a);
}

enum class Day : std::uint8_t {
    Monday = 1,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};


void test02_19_01() {
    // Before
    print_day(static_cast<std::underlying_type_t<Day>>(Day::Monday));

    // C++23
    print_day(std::to_underlying(Day::Friday));
}

void test02_19() {
    test02_19_01();
}
