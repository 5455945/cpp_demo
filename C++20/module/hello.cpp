// 模块实现单元(module implementation unit)
module hello;
// 在模块中使用import标准模块，需要在编译语句中指定/module:stdIfcDir 参数
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
