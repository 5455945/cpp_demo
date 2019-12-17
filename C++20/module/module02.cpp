module module02;

// 在模块中未使用基础库，极少数情况
// 编译时，必须指定/module:stdIfcDir
import std.core;
using namespace std;

namespace module02 {
    void say(const char* str) {
        cout << str << endl;
    }
}
