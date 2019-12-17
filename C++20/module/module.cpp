import std.core; // 使用标准导入模块
import module01; // 导入自定义模块
import hello;
import module02;

using namespace module01; // 使用自定义模块的命名空间

// 使用标准导入模块(import std.core;)
void use_standard_import_module() {
    std::cout << "hello world! use_standard_import_module" << std::endl;
}

int main(int argc, char** argv)
{
    use_standard_import_module();

    // 直接使用模块中的函数名
    std::cout << "module01::test(100) = " << test(100) << std::endl;

    hello::say_hello();
    hello::say_xz();
    hello::say_hi();
    module02::say("module02::say!");

    return 0;
}