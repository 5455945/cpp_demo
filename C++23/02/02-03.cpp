#include "02-03.h"

// 3、特性三：std::expected（P0323）
// 该特性旨在解决错误处理问题，并引入了一个新的头文件<expected>。
// 错误处理的逻辑关系是一个条件关系，即如果条件成立，则执行逻辑A；否则，执行逻辑B，并需要准确的错误信息来采取相应的措施。
// 目前常用的方式是使用错误码或异常，但这些方式使用起来仍然有许多不便之处。
// std::expected<T, E>表示期望，相当于std::variant和std::optional的结合体，
// 它可以保留T（期望的类型）或E（错误的类型），其接口与std::optional相似。以下是一个简单的例子：

#include <expected>
#include <string>
#include <iostream>

enum class Status : uint8_t {
    Ok,
    connection_error,
    no_authority,
    format_error,
};

bool connected() {
    return true;
}

bool has_authority() {
    return false;
}

bool format() {
    return false;
}

std::expected<std::string, Status> read_data() {
    if (!connected())
        return std::unexpected<Status> { Status::connection_error };
    if (!has_authority())
        return std::unexpected<Status> { Status::no_authority };
    if (!format())
        return std::unexpected<Status> { Status::format_error };

    return { "my expected type" };
}

void test02_03_01() {
    auto result = read_data();
    if (result) {
        std::cout << result.value() << "\n";
    }
    else {
        std::cout << "error code: " << (int)result.error() << "\n";
    }
}


void test02_03() {
    test02_03_01();
}