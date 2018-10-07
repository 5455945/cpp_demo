#include "../linq/LinqCpp.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void TestLinqCpp()
{
    using namespace cosmos;
    vector<int>v = { 0, 1, 2, 3, 4, 5, 3, 6 };
    vector<string> strv = { "a", "b", "c" };
    map<int, int> mymap = { { 1, 3 },{ 2, 1 },{ 3, 2 } };

    //�ۺ�
    string alstr = cosmos::from(strv).aggregate([](const string& str1, const string& str2) {
        return str1 + str2;
    });
    //�����abc

    //distinct
    sort(v); //distinct֮ǰҪ��������򲻶�
    auto result = from(v).where([](int x) {return x % 2 != 0; }).distinct().to_vector();
    //�����{0,1,2,3,4,5,6}��vector<int>���ϡ�

    //����
    auto ct = from(v).count();
    auto sm = from(v).sum();
    auto av = from(v).average();
    auto min = from(v).Min();
    auto max = from(v).Max();

    //Ԫ�ز�����
    auto elm = from(v).elementat(2);
    //�����2

    //��ת
    auto rv = from(v).reverse();

    //�������
    auto tk = from(v).take(3).to_vector();
    auto tkw = from(v).takewhile([](int a) {return a > 3; }); //���������������ľͷ��أ��ӿ�ʼ����ֹʱ�ķ�Χ

    auto skp = from(v).skip(3);
    auto skpw = from(v).skipwhile([](int a) {return a < 3; }).to_vector(); //������������end��Χ

    auto step = from(v).step(2); //�Բ���Ϊ2���������

                                 //ȡmap�еļ�����µ�����
    auto keys = from(mymap).keys();

    //ȡmap�е�ֵ����µ�����
    auto values = from(mymap).values();
}

int main() {
    TestLinqCpp();

    return 0;
}