#include "02-02.h"

// Monadic std::optional��P0798R8��

// P0798����Ϊstd::optional��������µĳ�Ա������map()��and_then()��or_else()����Щ�����Ĺ��ֱܷ�Ϊ��
// map()����optional�е�ֵӦ��һ��������������һ������Ӧ�ý����optional�����optional��û��ֵ���򷵻�һ���յ�optional��
// and_then()��������optional�ĺ����뵱ǰoptional���ʹ�á�
// or_else()�����optional�д���ֵ����ֱ�ӷ��ظ�optional��������ô���ĺ������������ 
// ��R2�У�map()��������Ϊtransform()�����ʵ����������������Ϊtransform()��and_then()��or_else()��
// ��Щ��������Ҫ�����Ǳ����ֶ����optionalֵ�Ƿ���Ч�����磺


//// Before
//if (opt_string) {
//	std::optional<int> i = stoi(*opt_string);
//}
//
//// After
//std::optional<int> i = opt_string.and_then(stoi);

#include <optional>
#include <string>

void test02_02_01() {
    // chain a series of functions until there's an error
    std::optional<std::string> opt_string("10");
    //std::optional<int> i = opt_string
    //    .and_then(std::stoi)
    //    .transform([](auto i) { return i * 2; });

    // fails, transform not called, j == nullopt
    std::optional<std::string> opt_string_bad("abcd");
    //std::optional<int> j = opt_string_bad
    //    .and_then(std::stoi)
    //    .transform([](auto i) { return j * 2; });
}

#include <iostream>
#include <optional>

struct A { /* ... */ };
struct B { /* ... */ };
struct C { /* ... */ };
struct D { /* ... */ };

auto A_to_B(A) -> B { /* ... */ std::cout << "A => B \n"; return {}; }
auto B_to_C(B) -> C { /* ... */ std::cout << "B => C \n"; return {}; }
auto C_to_D(C) -> D { /* ... */ std::cout << "C => D \n"; return {}; }

void try_transform_A_to_D(std::optional<A> o_A)
{
    std::cout << (o_A ? "o_A has a value\n" : "o_A is empty\n");

    std::optional<D> o_D = o_A.transform(A_to_B)
        .transform(B_to_C)
        .transform(C_to_D);

    std::cout << (o_D ? "o_D has a value\n\n" : "o_D is empty\n\n");
};

void test02_02_02()
{
    try_transform_A_to_D(A{});
    try_transform_A_to_D({});
}

#include <iostream>
#include <optional>
#include <string>

// optional ����������ʧ�ܵĹ����ķ�������
std::optional<std::string> create(bool b)
{
    if (b)
        return "Godzilla";
    return {};
}

// ���� std::nullopt �����κΣ��յģ� std::optional
auto create2(bool b)
{
    return b ? std::optional<std::string>{"Godzilla"} : std::nullopt;
}

void test02_02_03()
{
    std::cout << "create(false) ���� "
        << create(false).value_or("empty") << '\n';

    // ���� optional �Ĺ������������� while �� if ������
    if (auto str = create2(true))
        std::cout << "create2(true) ���� " << *str << '\n';
}


#include <charconv>
#include <iomanip>
#include <iostream>
#include <optional>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

std::optional<int> to_int(std::string_view sv)
{
    int r{};
    auto [ptr, ec] { std::from_chars(sv.data(), sv.data() + sv.size(), r) };
    if (ec == std::errc())
        return r;
    else
        return std::nullopt;
}

void test02_02_04()
{
    using namespace std::literals;

    const std::vector<std::optional<std::string>> v
    {
        "1234", "15 foo", "bar", "42", "5000000000", " 5", std::nullopt, "-43"
    };

    for (auto&& x : v | std::views::transform(
        [](auto&& o)
        {
            // debug print the content of input optional<string>
            std::cout << std::left << std::setw(13)
                << std::quoted(o.value_or("nullopt")) << " -> ";

            return o
                // if optional is nullopt convert it to optional with "" string
                .or_else([] { return std::optional{""s}; })
                // flatmap from strings to ints (making empty optionals where it fails)
                .and_then(to_int)
                // map int to int + 1
                .transform([](int n) { return n + 1; })
                // convert back to strings
                .transform([](int n) { return std::to_string(n); })
                // replace all empty optionals that were left by
                // and_then and ignored by transforms with "NaN"
                .value_or("NaN"s);
        }))
        std::cout << x << '\n';
}

void test02_02() {
    test02_02_01();
    test02_02_02();
    test02_02_03();
    test02_02_04();
}