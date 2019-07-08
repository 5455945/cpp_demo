//《基于MPI的大数据高性能计算导论》
// Frank Nielsen 张伟哲译 2018年7月第一版第一次印刷
// https://www.lix.polytechnique.fr/~nielsen/HPC4DS/

// filename: GrayString.cpp
// Naive recursive implementation of the Gray code using strings
#include <iostream>
#include <string>
using namespace std;

string* Mirror(string* s, int nb)
{
    string* res;
    res = new string[nb];
    int i;
    for (i = 0; i < nb; i++)
    {
        res[i] = s[nb - 1 - i]; // copie
    }
    return res;
}

string* GrayCode(int dim)
{
    string* res;
    int i, card = 1 << (dim - 1);

    if (dim == 1)
    {
        res = new string[2]; res[0] = "0";  res[1] = "1";
    }
    else
    {
        string* GC = GrayCode(dim - 1);
        string* GCreflected = Mirror(GC, card);
        res = new string[2 * card];

        // prefixe
        for (i = 0; i < card; i++)
        {
            res[i] = "0" + GC[i];
            res[i + card] = "1" + GCreflected[i];
        }
    }
    return res;
}


void printCode(string* code, int nb)
{
    int i;
    for (i = 0; i < nb; i++)
    {
        cout << code[i] << endl;
    }
}

// GrayString.exe
int main()
{
    int i, dim = 4;
    string* GC = GrayCode(dim);
    printCode(GC, 1 << dim);

    return 0;
}
