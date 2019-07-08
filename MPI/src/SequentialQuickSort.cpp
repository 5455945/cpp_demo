//《基于MPI的大数据高性能计算导论》
// Frank Nielsen 张伟哲译 2018年7月第一版第一次印刷
// https://www.lix.polytechnique.fr/~nielsen/HPC4DS/

// filename: SequentialQuickSort.cpp
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>

using namespace std;
// pivot
template <class T>
void quickSort(vector<T>& v, unsigned int low, unsigned int high)
{
    if (low >= high) return;
    // select median element for the pivot
    unsigned int pivotIndex = (low + high) / 2;
    // partition
    pivotIndex = pivot(v, low, high, pivotIndex);
    // sort recursively
    if (low < pivotIndex) quickSort(v, low, pivotIndex);
    if (pivotIndex < high)  quickSort(v, pivotIndex + 1, high);
}

template <class T> void quickSort(vector<T>& v)
{
    unsigned int numberElements = (unsigned int)v.size();
    if (numberElements > 1)
        quickSort(v, 0, numberElements - 1);
}

template <class T>
unsigned int pivot(vector<T>& v, unsigned int start,
    unsigned int stop, unsigned int position)
{//swap pivot with initial position
    swap(v[start], v[position]);
    // partition values
    unsigned int low = start + 1;
    unsigned int high = stop;
    while (low < high)
        if (v[low] < v[start])
            low++;
        else if (v[--high] < v[start])
            swap(v[low], v[high]);
    // swap again pivot with initial element 
    swap(v[start], v[--low]);
    return low;
}
// SequentialQuickSort.exe
void main() {
    vector<int> v(100);
    for (int i = 0; i < 100; i++) {
        v[i] = rand();
    }
    quickSort<int>(v);
    vector<int>::iterator itr = v.begin();
    while (itr != v.end()) {
        std::cout << *itr << " ";
        itr++;
    }
    std::cout << std::endl;
}
// 运行结果
//```
//SequentialQuickSort.exe
//41 153 288 292 491 778 1842 1869 2082 2995 3035 3548 3902 4664 4827 4966 5436 5447 5537 5705 6334 6729 6868 7376 7711 8723 8942 9040 9741 9894 9961 11323 11478 11538 11840 11942 12316 12382 12623 12859 13931 14604 14771 15006 15141 15350 15724 15890 16118 16827 16944 17035 17421 17673 18467 18716 18756 19169 19264 19629 19718 19895 19912 19954 20037 21538 21726 22190 22648 22929 23281 23805 23811 24084 24370 24393 24464 24626 25547 25667 26299 26308 26500 26962 27446 27529 27644 28145 28253 28703 29358 30106 30333 31101 31322 32391 32439 32662 32757 16541
//```
