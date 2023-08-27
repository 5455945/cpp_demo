#include "02-06.h"

// 6����������Formatted Output��P2093��
// ���᰸ָ����std::print()��֮ǰ�Ѿ��ᵽ���������ټ�˵��һ�¡�
//
// ��׼��cout��Ʒǳ���⣬��Ҫ�����ڿ����Բ����û�и�ʽ�����������ε��ø�ʽ��I / O������
// Ĭ�ϻ�ͬ����׼C�������ܵ͡������ɲ���������ɣ��ڶ��̻߳����»ᵼ�����ݴ�����ʾ��������ռ�ÿռ������⡣
//
// Ϊ�˽����Щ���⣬������Formatting Library����C++20�м���������fmt����ʹ�ö����fmt::print()��
// ����������ԡ�Unicode����֧�֡����õ����ܺͽ�С�Ķ�����ռ�ÿռ��Ҫ��
//
// Ϊ�˲�Ӱ�����д��룬������ר�������һ���µ�ͷ�ļ������а���������Ҫ������

#include <print>

void test02_06_01() {
    const char* world = "world";
    std::print("Hello {}", world);   // doesn't print a newline
    std::println("Hello {}", world); // print a newline
}

// std::print����cout��˵��ֱ�������Ĵ�������������Ժ�����ԶԶ������cout��
// std::print���﷨����Formatting Library�ĸ�ʽ���﷨�����Բο�Using C++20 Formatting Library�����ܷ���ĶԱ����£�

/*
```
----------------------------------------------------------
Benchmark                Time             CPU   Iterations
----------------------------------------------------------
printf                87.0 ns         86.9 ns      7834009
ostream                255 ns          255 ns      2746434
print                 78.4 ns         78.3 ns      9095989
print_cout            89.4 ns         89.4 ns      7702973
print_cout_sync       91.5 ns         91.4 ns      7903889
```
*/

// ���Խ����ʾ��printf��print��ִ���ٶȼ�����cout��������printĬ�ϻὫ�����ӡ��stdout��
// ���������ӡ��cout��ͬ����׼C����ʱ��print_cout_sync����print���ٶȴ�ű�cout��14% ��
// ����ͬ����׼C����ʱ��print_cout�����ٶ���ȻҪ��öࡣ


void test02_06() {
    test02_06_01();
}