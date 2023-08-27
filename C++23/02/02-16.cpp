#include "02-16.h"

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>  // std::quoted
#include <span> // std::span
#include <cassert>

// 16������ʮ����Improving string and string_view��P1679R3, P2166R1, P1989R2, P1072R10, P2251R1��
// ���string��string_view��P1679�����һЩ��ǿ������֮һ��������һ��contain()������������һ��С���ӣ�


void test02_16_01() {
    std::string str("dummy text");
    if (str.contains("dummy")) {
        // do something
    }
}

// Ŀǰ��GCC 11��Clang 12��MSVC v19.30�Ѿ�֧�ָ����ԡ� P2166ʹ�ô�nullptr�������ǲ��ٲ���δ������Ϊ������ֱ�ӵ��±���ʧ�ܡ�

void test02_16_02() {
    //std::string s{ nullptr };       // error!
    //std::string_view sv{ nullptr }; // error!
}

// Ŀǰ��GCC 12��Clang 13��MSVC v19.30�Ѿ�֧�ָ����ԡ� P1989�����std::string_view�ģ�������һ��С���ӣ�
void test02_16_03() {
    std::vector v{ 'a', 'b', 'c' };
    
    // Before
    std::string_view sv(v.begin(), v.end());
    
    // After
    std::string_view sv23{ v };
}

// ��ǰ�޷�ֱ�Ӵ�Ranges����std::string_view���������ַ�ʽ�õ���֧�֡� 
// �������Ѿ���GCC 11��Clang 14��MSVC v19.30��֧�֡�
// ���string��P1072������һ����Ա������
// template< class Operation >
// constexpr void resize_and_overwrite(size_type count, Operation op);
// ���ǿ���ͨ���᰸�е�һ��ʾ�������������ԣ�

void test02_16_04() {
    std::string s{ "Food: " };

    s.resize_and_overwrite(10, [](char* buf, int n) {
        return std::find(buf, buf + n, ':') - buf;
        });

    std::cout << std::quoted(s) << '\n'; // "Food"
}

// ���������Ҫ���������������ı��С�͸������ݡ���һ���������µĴ�С���ڶ���������һ�������������������µ����ݡ�
// Ȼ����߼��ǣ����maxsizeС�ڵ���s�Ĵ�С��ɾ������size()-maxsize��Ԫ�أ����maxsize����s�Ĵ�С��
// ׷��maxsize-size()��Ĭ��Ԫ�أ�������erase(begin() + op(data(), maxsize), end())��
// �����ṩһ�����ӣ�����ʹ�������߼������ú�����

void test02_16_05() {
    constexpr std::string_view fruits[]{ "apple", "banana", "coconut", "date", "elderberry" };
    std::string s1{ "Food: " };

    //s1.resize_and_overwrite(16, [sz = s1.size()](char* buf, std::size_t buf_size) {
    //    const auto to_copy = std::min(buf_size - sz, fruits[1].size()); // 6
    //    std::memcpy(buf + sz, fruits[1].data(), to_copy); // append "banana" to s1.
    //    return sz + to_copy; // 6 + 6
    //    });

    std::cout << s1; // Food: banana
}

#define ASSERT_EQUAL(a, b) assert(a == b)
#define ASSERT(a) assert(a)
void test02_16_06() {
    char input[] = "10 20 30";
    //std::ispanstream is{ std::span<char>{input} };
    //int i;
    //
    //is >> i;
    //ASSERT_EQUAL(10, i);
    //
    //is >> i;
    //ASSERT_EQUAL(20, i);
    //
    //is >> i;
    //ASSERT_EQUAL(30, i);
    //
    //is >> i;
    //ASSERT(!is);
}


void test02_16() {
    test02_16_01();
    test02_16_02();
    test02_16_03();
    test02_16_04();
    test02_16_05();
    test02_16_06();
}
