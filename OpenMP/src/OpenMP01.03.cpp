#include "OpenMP01.03.h"
#include "omp.h"
#include <array>
#include <iostream>

// OPENMP ʵ�ֿ�������
void quickSort(int* num, int low, int high);  // ���з���
int Partition(int * num, int low, int high);   // ���ط����

void quickSort(int* num, int low, int high)
{
    if (low < high)
    {
        int split = Partition(num, low, high);
#pragma omp parallel sections // ��������
        {
#pragma omp section  // �������������̶߳�ǰ�沿�ֽ�������
            quickSort(num, low, split - 1);
#pragma omp section  // �������������̶߳Ժ��沿�ֽ�������
            quickSort(num, split + 1, high);
        }
    }
}

int Partition(int* num, int low, int high)
{
    int temp = num[low];  // ��Ϊ����
    while (low < high)
    {
        while (low < high&&num[high] >= temp)high--;
        num[low] = num[high];
        while (low < high&&num[low] <= temp)low++;
        num[high] = num[low];
    }
    num[low] = temp;
    return low;  // ���������λ�ã��ٽ��з���
}

void test0103() {
    int num[] = { 2, 3, 5, 623, 32, 4324, 3, 24 };
    quickSort(num, 0, 7);
    int i;
    for (i = 0; i < 8; i++) {
        printf("%d\n", num[i]);
    } 
}

// https://blog.csdn.net/Real_Myth/article/details/52574300
