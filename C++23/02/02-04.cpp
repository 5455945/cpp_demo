#include "02-04.h"

// 4�������ģ�Multidimensional Arrays��P2128��
// ����������ڷ��ʶ�ά���顣��ǰ��C++��operator[]ֻ֧�ַ��ʵ����±꣬�޷����ʶ�ά���顣
// ��ˣ�Ϊ�˷��ʶ�ά���飬��ǰ�ķ����ǣ�
// ����operator()��Ȼ��Ϳ���ʹ��m(1, 2)�����ʵ�1�е�2�е�Ԫ�ء����ǣ����ַ��������뺯�����ò���������
// ����operator[]��ʹ��std::initializer_list��Ϊ������Ȼ��Ϳ���ʹ��m[{1, 2}]������Ԫ�ء����ǣ����ַ�������������֣�
// ��ʽ����operator[]��Ȼ��Ϳ���ʹ��m[1][2]������Ԫ�ء�ͬ�������ַ�ʽҲ����֡�����һ��at()��Ա������Ȼ��ʹ��at(1, 2)������Ԫ��Ҳ��̫���㡣
// C++23���ڿ���ͨ��m[1, 2]���ַ�ʽ�����ʶ�ά�����ˡ�������һ�����ӣ�
#include <array>
#include <iostream>
/*
template <class T, size_t R, size_t C>
struct matrix {
    T& operator[](const size_t r, const size_t c) noexcept {
        return data_[r * C + c];
    }

    const T& operator[](const size_t r, const size_t c) const noexcept {
        return data_[r * C + c];
    }

private:
    std::array<T, R* C> data_;
};


void test02_04_01() {
    matrix<int, 2, 2> m;
    m[0, 0] = 0;
    m[0, 1] = 1;
    m[1, 0] = 2;
    m[1, 1] = 3;

    for (auto i = 0; i < 2; ++i) {
        for (auto j = 0; j < 2; ++j) {
            std::cout << m[i, j] << ' ';
        }
        std::cout << std::endl;
    }
}
*/

void test02_04() {
    //test02_04_01();
}