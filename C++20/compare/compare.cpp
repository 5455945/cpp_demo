#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <compare> // 重点是三路比较运算符 operator<=>

// 默认比较(C++20起)
// https://zh.cppreference.com/w/cpp/language/default_comparisons
// 提供一种方式，以要求编译器为某个类生成相一致的关系运算符。
// 简言之，定义了 operator<=> 的类自动获得由编译器生成的运算符 == 、 != 、<、 <= 、> 和 >= 。
// 类可以将 operator<=> 定义为预置的，这种情况下编译器亦将为该运算符生成代码。

class Point {
    int x;
    int y;
public:
    Point(int a, int b) :x(a), y(b) {}
    auto operator<=>(const Point&) const = default; // 预置 operator<=>
    // 因为预置 operator<=>，现在能用 ==、!=、<、<=、> 和 >= 比较 Point
    // ……非比较函数……
};
void test_compare01() {
    // 编译器生成全部四个关系运算符
    Point pt1{ 1, 2 }, pt2{1, 3};
    std::set<Point> s; // OK
    s.insert(pt1); // OK
    s.insert(pt2);
    if (pt1 <= pt2) { std::cout << "pt1 <= pt2\n"; } // OK，只调用一次 <=>
    else { std::cout << "! (pt1 <= pt2)\n"; }
}

class Base {
public:
    auto operator<=>(const Base&) const = default;
};
std::strong_ordering operator<=>(const std::string& a, const std::string& b) {
    int cmp = a.compare(b);
    if (cmp < 0) return std::strong_ordering::less;
    else if (cmp > 0) return std::strong_ordering::greater;
    else return std::strong_ordering::equivalent;
}
class TotallyOrdered : Base {
    std::string tax_id;
    std::string first_name;
    std::string last_name;
public:
    TotallyOrdered(const std::string& id, const std::string& first, const std::string& last) 
        :tax_id(id), first_name(first), last_name(last) {}
    // 定制 operator<=>，因为我们想先比较姓
    std::strong_ordering operator<=>(const TotallyOrdered& that) const {
        if (auto cmp = (Base&)(*this) <=> (Base&)that; cmp != 0) return cmp;
        if (auto cmp = last_name <=> that.last_name; cmp != 0) return cmp;
        if (auto cmp = first_name <=> that.first_name; cmp != 0) return cmp;
        return tax_id <=> that.tax_id;
    }
    // ……非比较函数……
};
void test_compare02() {
    // 编译器生成全部四个关系运算符
    TotallyOrdered to1{ "1", "first1", "last1" }, to2{ "2", "first2", "last2" };
    std::set<TotallyOrdered> s; // ok
    s.insert(to1); // ok
    s.insert(to2);
    if (to1 <= to2) { // ok，调用一次 <=>
        std::cout << "to1 <= to2\n";
    }
    else {
        std::cout << "!(to1 <= to2)\n";
    }
}

class CaseInsensitiveString {
    std::string s;
    std::weak_ordering case_insensitive_compare(
        const char* a, const char* b) const {
        int cmp = _stricmp(a, b);
        if (cmp < 0) return std::weak_ordering::less;
        else if (cmp > 0) return std::weak_ordering::greater;
        else return std::weak_ordering::equivalent;
    }
public:
    CaseInsensitiveString(const std::string& str) : s(str) {}
    std::weak_ordering operator<=>(const CaseInsensitiveString& b) const {
        return case_insensitive_compare(s.c_str(), b.s.c_str());
    }
    std::weak_ordering operator<=>(const char* b) const {
        return case_insensitive_compare(s.c_str(), b);
    }
    // ……非比较函数……
};

void test_compare03() {
    // 编译器生成全部四个关系运算符
    CaseInsensitiveString cis1{ "XYzza" }, cis2{ "xyzza" };
    std::set<CaseInsensitiveString> s; // ok
    s.insert(cis1); // ok
    s.insert(cis2);
    if (cis1 <= cis2) {// ok，进行一次比较运算
        std::cout << "cis1 <= cis2\n";
    } 

    // 编译器亦生成全部八个异相关系运算符
    if (cis1 <= "xyzzy") {// ok，进行一次比较运算
        std::cout << "cis1 <= \"xyzzy\"\n";
    }
    if ("xyzzy" >= cis1) {// ok，等同的语义
        std::cout << "\"zyzzy\" >= cis1\n";
    }
}

class PersonInFamilyTree {
private:
    int parent_family_level_id = -1;
    int self_family_level_id = -1;

    bool is_the_same_person_as(const PersonInFamilyTree& rhs) const {
        return (self_family_level_id >= 0 &&
            (self_family_level_id == rhs.self_family_level_id));
    }
    bool is_transitive_child_of(const PersonInFamilyTree& rhs) const {
        return (rhs.self_family_level_id >= 0 && 
            (parent_family_level_id == rhs.self_family_level_id));
    }
public:
    PersonInFamilyTree(int parent, int self) :
        parent_family_level_id(parent), self_family_level_id(self) {}
    std::partial_ordering operator<=>(const PersonInFamilyTree& that) const {
        if (this->is_the_same_person_as(that)) return std::partial_ordering::equivalent;
        if (this->is_transitive_child_of(that)) return std::partial_ordering::less;
        if (that.is_transitive_child_of(*this)) return std::partial_ordering::greater;
        return std::partial_ordering::unordered;
    }
    // ……非比较函数……
};
void test_compare04() {
    // 编译器生成全部四个关系运算符
    PersonInFamilyTree per1{ 0, 1 }, per2{ 1, 10 };
    if (per1 < per2) {
        std::cout << "ok， per2 是 per1 的祖先\n";
    } 
    else if (per1 > per2) {
        std::cout << "ok, per1 是 per2 的祖先\n";
    }
    else if (std::is_eq(per1 <=> per2)) {
        std::cout << "ok， per1 即是 per2\n";
    }
    else {
        std::cout << "per1 与 per2 无关\n";
    }
    if (per1 <= per2) {
        std::cout << "ok， per2 是 per1 或 per1 的祖先\n";
    }
    if (per1 >= per2) {
        std::cout << "ok， per1 是 per2 或 per2 的祖先\n";
    }
    if (std::is_neq(per1 <=> per2)) {
        std::cout << "ok， per1 不是 per2\n";
    }
}

// https://zh.cppreference.com/w/cpp/utility/compare/compare_three_way
struct Rational_2 {
    int num;
    int den; // > 0
};

constexpr std::weak_ordering operator<=>(Rational_2 lhs, Rational_2 rhs)
{
    return lhs.num * rhs.den <=> rhs.num * lhs.den;
}

void print(std::weak_ordering value)
{
    if (value == 0)
        std::cout << "equal\n";
    else if (value < 0)
        std::cout << "less\n";
    else
        std::cout << "greater\n";
}

void test_compare05() {
    Rational_2 c{ 6,5 };
    Rational_2 d{ 8,7 };
    print(c <=> d);
    //print(std::compare_three_way{}(c, d));
}

int main()
{
    test_compare01();
    test_compare02();
    test_compare03();
    test_compare04();
    test_compare05();
    return 0;
}

