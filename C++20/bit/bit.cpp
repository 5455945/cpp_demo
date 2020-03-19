#include <bit>
#include <bitset>
#include <concepts>
//#include <cmath>
#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <numeric>

// 01 vs2019 16.5 的<bit>中并没有提供std::bit_cast
// https://zh.cppreference.com/w/cpp/numeric/bit_cast
namespace std {
    template <class To, class From>
    typename std::enable_if<
        (sizeof(To) == sizeof(From)) &&
        std::is_trivially_copyable<From>::value&&
        std::is_trivial<To>::value,
        // 此实现要求 To 可平凡默认构造
        To>::type
        // constexpr 支持需要编译器魔法
        bit_cast(const From& src) noexcept
    {
        To dst;
        std::memcpy(&dst, &src, sizeof(To));
        return dst;
    }

    //// https://zh.cppreference.com/w/cpp/concepts/unsigned_integral
    //template < class T >
    //concept unsigned_integral = std::integral<T> && !std::signed_integral<T>;

    // 02 vs2019 16.5 的<bit>中并没有提供std::has_single_bit
    // https://zh.cppreference.com/w/cpp/numeric/has_single_bit
    template <std::unsigned_integral T>
    requires !std::same_as<T, bool> && !std::same_as<T, char>
    constexpr bool has_single_bit(T x) noexcept
    {
        return x != 0 && (x & (x - 1)) == 0;
    }
}

//constexpr double f64v = 19880124.0;
//constexpr auto u64v = std::bit_cast<std::uint64_t>(f64v);
//
//constexpr std::uint64_t u64v2 = 0x3fe9000000000000ull;
//constexpr auto f64v2 = std::bit_cast<double>(u64v2);

constexpr double f64v = 19880124.0;
auto u64v = std::bit_cast<std::uint64_t>(f64v);

constexpr std::uint64_t u64v2 = 0x3fe9000000000000ull;
auto f64v2 = std::bit_cast<double>(u64v2);

// https://zh.cppreference.com/w/cpp/numeric/bit_cast
void bit_test01()
{
    std::cout
        << std::fixed << f64v << "f64.to_bits() == 0x"
        << std::hex << u64v << "u64\n";

    std::cout
        << "f64::from_bits(0x" << std::hex << u64v2 << "u64) == "
        << std::fixed << f64v2 << "f64\n";
    //19880124.000000f64.to_bits() == 0x4172f58bc0000000u64
    //f64::from_bits(0x3fe9000000000000u64) == 0.781250f64
}

// https://zh.cppreference.com/w/cpp/numeric/has_single_bit
void bit_test02() {
    std::cout << std::boolalpha;
    for (auto i = 0u; i < 10u; ++i) {
        std::cout << "has_single_bit(" << i << ") = " << std::has_single_bit(i) << '\n';
    }
}

void bit_ceil_floor() {
    //// https://zh.cppreference.com/w/cpp/numeric/bit_ceil
    //std::cout << std::ceil2(unsigned short(0)) << std::endl;
    //// https://zh.cppreference.com/w/cpp/numeric/bit_floor
    //std::cout << std::floor2(unsigned short(24)) << std::endl;
}

// https://zh.cppreference.com/w/cpp/numeric/bit_width
// 此函数等价于 return std::numeric_limits<T>::digits - std::countl_zero(x);
void bit_width_test() {

}

// https://zh.cppreference.com/w/cpp/numeric/rotl
void bit_rotl() {
    //std::uint8_t i = 0b00011101;
    //std::cout << "i          = " << std::bitset<8>(i) << '\n';
    //std::cout << "rotl(i,0)  = " << std::bitset<8>(std::rotl(i, 0)) << '\n';
    //std::cout << "rotl(i,1)  = " << std::bitset<8>(std::rotl(i, 1)) << '\n';
    //std::cout << "rotl(i,4)  = " << std::bitset<8>(std::rotl(i, 4)) << '\n';
    //std::cout << "rotl(i,9)  = " << std::bitset<8>(std::rotl(i, 9)) << '\n';
    //std::cout << "rotl(i,-1) = " << std::bitset<8>(std::rotl(i, -1)) << '\n';
}

// https://zh.cppreference.com/w/cpp/numeric/rotr
void bit_rotr() {
    //std::uint8_t i = 0b00011101;
    //std::cout << "i          = " << std::bitset<8>(i) << '\n';
    //std::cout << "rotr(i,0)  = " << std::bitset<8>(std::rotr(i, 0)) << '\n';
    //std::cout << "rotr(i,1)  = " << std::bitset<8>(std::rotr(i, 1)) << '\n';
    //std::cout << "rotr(i,9)  = " << std::bitset<8>(std::rotr(i, 9)) << '\n';
    //std::cout << "rotr(i,-1) = " << std::bitset<8>(std::rotr(i, -1)) << '\n';
}

// https://zh.cppreference.com/w/cpp/numeric/countl_zero
void bit_countl_zero() {
    //for (std::uint8_t i : { 0, 0b11111111, 0b00011100 }) {
    //    std::cout << "countl_zero(0b" << std::bitset<8>(i) << ") = "
    //        << std::countl_zero(i) << '\n';
    //}
}

// https://zh.cppreference.com/w/cpp/numeric/countl_one
void bit_countl_one() {
    //for (std::uint8_t i : { 0, 0b11111111, 0b11100011 }) {
    //    std::cout << "countl_one(0b" << std::bitset<8>(i) << ") = "
    //        << std::countl_one(i) << '\n';
    //}
}

// https://zh.cppreference.com/w/cpp/numeric/countr_zero
void bit_countr_zero() {
    //for (std::uint8_t i : { 0, 0b11111111, 0b00011100 }) {
    //    std::cout << "countr_zero(0b" << std::bitset<8>(i) << ") = "
    //        << std::countr_zero(i) << '\n';
    //}
}

// https://zh.cppreference.com/w/cpp/numeric/countr_one
void bit_countr_one() {
    //for (std::uint8_t i : { 0, 0b11111111, 0b11100011 }) {
    //    std::cout << "countr_one(0b" << std::bitset<8>(i) << ") = "
    //        << std::countr_one(i) << '\n';
    //}
}

// https://zh.cppreference.com/w/cpp/numeric/popcount
void bit_popcount() {
    //for (std::uint8_t i : { 0, 0b11111111, 0b00011101 }) {
    //    std::cout << "popcount(0b" << std::bitset<8>(i) << ") = "
    //        << std::popcount(i) << '\n';
    //}
}

// https://zh.cppreference.com/w/cpp/types/endian
//enum class endian
//{
//#ifdef _WIN32
//    little = 0,
//    big = 1,
//    native = little
//#else
//    little = __ORDER_LITTLE_ENDIAN__,
//    big = __ORDER_BIG_ENDIAN__,
//    native = __BYTE_ORDER__
//#endif
//};
void bit_endian() {
    if (std::endian::little == std::endian::native) {
        std::cout << "std::endian::little" << std::endl;
    }
    else if (std::endian::big == std::endian::native) {
        std::cout << "std::endian::big" << std::endl;
    }
    else {
        std::cout << "std::endian::other" << std::endl;
    }
}

// https://zh.cppreference.com/w/cpp/numeric/midpoint
void test_numeric_midpoint() {
    // 计算整数、浮点或指针 a 与 b 的中点。
    std::uint32_t a = std::numeric_limits<std::uint32_t>::max();
    std::uint32_t b = std::numeric_limits<std::uint32_t>::max() - 2;

    std::cout << "a: " << a << '\n'
        << "b: " << b << '\n'
        << "Incorrect (overflow and wrapping): " << (a + b) / 2 << '\n'
        << "Correct: " << std::midpoint(a, b) << '\n';
}

// https://zh.cppreference.com/w/cpp/numeric/lerp
void test_cmath_lerp() {
    std::cout << "$a + t(b - a)$ = " << std::lerp(1., 5., 2) << std::endl;
}

int main() {
    bit_test01();
    bit_test02();
    bit_ceil_floor();
    bit_width_test();
    bit_rotl();
    bit_rotr();
    bit_countl_zero();
    bit_countl_one();
    bit_countr_zero();
    bit_countr_one();
    bit_popcount();
    bit_endian();

    test_numeric_midpoint();
    test_cmath_lerp();
    return 0;
}