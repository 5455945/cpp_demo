#include <iostream>
// 这里的gsl::span是微软的一个开源实现
// https://github.com/microsoft/GSL/tree/master/include/gsl
#include <gsl/gsl>

using namespace std;

// 《C++语言导论》 P147 13.3 范围检查:span
void fpn(int* p, int n) { // p可以是一个内置数组
    for (int i = 0; i < n; i++) {
        p[i] = 1;
    }
}

void use(int x) {
    int a[100];  // 内置数组
    fpn(a, 100);       // 正确
    //fpn(a, 1000);      // 糟糕，范围越界,(0xC0000005: 写入位置 0x000000E546F00000 时发生访问冲突。)
    //fpn(a + 10, 100);  // fpn中产生范围错误,(Run-Time Check Failure #2 - Stack around the variable 'a' was corrupted.)
    //fpn(a, x);         // 可疑的，但看起来无事,(x>100,Run-Time Check Failure #2 - Stack around the variable 'a' was corrupted.)
}

void fs(gsl::span<int> p) {
    for (auto& x : p) {
        x = 2;
    }
}

void use_span(int x) {
    int a[100];
    fs(a);               // 隐式创建一个span<int>{a, 100}
    //fs({ a, 1000 });     // 错误:期待一个sapn
    //fs({ a + 10, 100 }); // 在fs中发生范围错误,(Run-Time Check Failure #2 - Stack around the variable 'a' was corrupted.)
    //fs({ a, x });        // 明显可疑,(x>100,Run-Time Check Failure #2 - Stack around the variable 'a' was corrupted.)
}

// C++核心准则边译边学-X.4：使用span解决数组退化和越界访问
// https://blog.csdn.net/craftsman1970/article/details/103217292
void traditional_array(int buffer[], size_t size)
{
    cout << "size=" << size << endl;
    for (int i = 0; i < int(size); ++i) {
        buffer[i] = i;
    }
    buffer[0] = int(size * 2);
    //buffer[size * 2] = int(size * 4);  // 传统数组越界访问
}

void span_array(gsl::span<int> buffer)
{
    cout << "size=" << buffer.size() << endl;
    int value = 0;
    for (auto it = buffer.begin(); it != buffer.end(); it++) {
        *it = value++;
    }
    buffer[0] = value++;
    //buffer[buffer.size() * 2] = value++; // span会触发断言
}

int main()
{
    int x = 105;
    use(x);
    use_span(x);

    int data[10]; // 内置数组
    for (size_t i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
        data[i] = 0;
    }
    // 使用数组传递参数
    traditional_array(data, 5);
    // 使用span传递参数
    span_array(data);

    gsl::span<int> sdata = data;
    for (auto v : sdata) {
        std::cout << v << ", ";
    }
    std::cout << std::endl;

    return 0;
}
