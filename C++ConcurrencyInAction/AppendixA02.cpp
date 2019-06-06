#include "AppendixA.h"
#include <memory>
#include <string>
namespace {
    using my_class = std::string;
    class move_only
    {
        std::unique_ptr<my_class> data;
    public:
        move_only(const move_only&) = delete;
        move_only(move_only&& other) :
            data(std::move(other.data))
        {}
        move_only& operator=(const move_only&) = delete;
        move_only& operator=(move_only&& other)
        {
            data = std::move(other.data);
            return *this;
        }
    };
}
void AppendixA_02() {
    //move_only m1;    // 错误
    //move_only m2(m1); // 错误，拷贝构造函数声明为删除的
    //move_only m3(std::move(m1)); // 正确，找到移动构造函数
}
