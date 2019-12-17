module module01;

// 在模块中未使用基础库，极少数情况
// 编译时，可以不指定/module:stdIfcDir
namespace module01 {

    int test(int x)
    {
        return x * x;
    }
}
