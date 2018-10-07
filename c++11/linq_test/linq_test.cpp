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

    //聚合
    string alstr = cosmos::from(strv).aggregate([](const string& str1, const string& str2) {
        return str1 + str2;
    });
    //将输出abc

    //distinct
    sort(v); //distinct之前要先排序否则不对
    auto result = from(v).where([](int x) {return x % 2 != 0; }).distinct().to_vector();
    //将输出{0,1,2,3,4,5,6}的vector<int>集合。

    //计算
    auto ct = from(v).count();
    auto sm = from(v).sum();
    auto av = from(v).average();
    auto min = from(v).Min();
    auto max = from(v).Max();

    //元素操作符
    auto elm = from(v).elementat(2);
    //将输出2

    //反转
    auto rv = from(v).reverse();

    //区间操作
    auto tk = from(v).take(3).to_vector();
    auto tkw = from(v).takewhile([](int a) {return a > 3; }); //遇到不满足条件的就返回，从开始到终止时的范围

    auto skp = from(v).skip(3);
    auto skpw = from(v).skipwhile([](int a) {return a < 3; }).to_vector(); //不满足条件到end范围

    auto step = from(v).step(2); //以步长为2组成新序列

                                 //取map中的键组成新的序列
    auto keys = from(mymap).keys();

    //取map中的值组成新的序列
    auto values = from(mymap).values();
}

int main() {
    TestLinqCpp();

    return 0;
}