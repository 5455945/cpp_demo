// ģ��ʵ�ֵ�Ԫ(module implementation unit)
module hello;
// ��ģ����ʹ��import��׼ģ�飬��Ҫ�ڱ��������ָ��/module:stdIfcDir ����
import std.core;
using namespace std;

namespace hello {

    void say_hi() {
        cout << "hello hi!" << endl;
    }

    void say_hello() {
        cout << "hello world!" << endl;
    }

    void say_xz() {
        cout << "hello xz!" << endl;
    }
}
