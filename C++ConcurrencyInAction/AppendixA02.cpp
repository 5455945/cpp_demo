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
    //move_only m1;
    //move_only m2(m1);
    //move_only m3(std::move(m1));
}
