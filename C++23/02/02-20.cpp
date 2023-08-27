#include "02-20.h"

#include <bit>
#include <print>
#include <type_traits>

// 20�����Զ�ʮ��std::byteswap��P1272R4��
// λ��<bit>������˼�壬�ǹ���λ�����ġ�
// ������һ��ʾ�����Ա���õ���⣺

template <std::integral T>
void print_hex(T v)
{
    for (std::size_t i = 0; i < sizeof(T); ++i, v >>= 8)
    {
        std::print("{:02X} ", static_cast<unsigned>(T(0xFF) & v));
    }
    std::print("{}", '\n');
}

void test02_20_01()
{
    unsigned char a = 0xBA;
    print_hex(a);                     // BA
    print_hex(std::byteswap(a));      // BA
    unsigned short b = 0xBAAD;
    print_hex(b);                     // AD BA
    print_hex(std::byteswap(b));      // BA AD
    int c = 0xBAADF00D;
    print_hex(c);                     // 0D F0 AD BA
    print_hex(std::byteswap(c));      // BA AD F0 0D
    long long d = 0xBAADF00DBAADC0FE;
    print_hex(d);                     // FE C0 AD BA 0D F0 AD BA
    print_hex(std::byteswap(d));      // BA AD F0 0D BA AD C0 FE
}
// �������ܹ���ת���͵��ֽ��򣬳����������ݴ�������д���ͬϵͳʹ�ò�ͬ�ֽ��򣨴��С�ˣ��������

void test02_20() {
    test02_20_01();
}
