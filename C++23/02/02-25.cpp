#include "02-25.h"

#include <cstddef>
#include <print>
#include <vector>
//#include <mdspan> // msvc 19.37 ��֧��
//#include "raw.githubusercontent.com_kokkos_mdspan_single-header_mdspan.hpp"


// 25�����Զ�ʮ�壺std::mdspan��P0009r18��
// ������һ���򵥵����ӣ�չʾ�����ʹ��std::mdspan�������Ͳ�����ά���飺

// https://en.cppreference.com/w/cpp/container/mdspan
void test02_25_01()
{
//    std::vector v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
//
//    // View data as contiguous memory representing 2 rows of 6 ints each
//    auto ms2 = std::mdspan(v.data(), 2, 6);
//    // View the same data as a 3D array 2 x 3 x 2
//    auto ms3 = std::mdspan(v.data(), 2, 3, 2);
//
//    // write data using 2D view
//    for (std::size_t i = 0; i != ms2.extent(0); i++)
//        for (std::size_t j = 0; j != ms2.extent(1); j++)
//            ms2[i, j] = i * 1000 + j;
//
//    // read back using 3D view
//    for (std::size_t i = 0; i != ms3.extent(0); i++)
//    {
//        std::println("slice @ i = {}", i);
//        for (std::size_t j = 0; j != ms3.extent(1); j++)
//        {
//            for (std::size_t k = 0; k != ms3.extent(2); k++)
//                std::print("{} ", ms3[i, j, k]);
//            std::println("");
//        }
//    }
}


// Ŀǰû�б�����֧�ָ����ԣ�ʹ�õ���https://raw.githubusercontent.com/kokkos/mdspan/single-header/mdspan.hppʵ�ֵİ汾��
// // ������experimental���档
// ms2�ǽ������Զ�ά��ʽ���ʣ�ms3������ά���ʣ�Views���Ըı�ԭ�����ݣ�������ձ����Ľ��Ϊ��


void test02_25() {

}
