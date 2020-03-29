#include <iostream>
#include <string_view>
// https://github.com/paweldac/source_location
#include "source_location.hpp"

// https://zh.cppreference.com/w/cpp/header/source_location
// https://zh.cppreference.com/w/cpp/utility/source_location
void log(const std::string_view& message, const std::source_location& location = std::source_location::current())
{
    std::cout << "info: "
        << location.file_name() << " "
        << location.function_name() << " "
        << location.line() << " "
        << location.column() << " "
        << message << '\n';
}

int main()
{
    auto location = std::source_location::current();
    std::cout << "info: " << location.file_name() << ":" << location.line() << ":"
        << location.column() << ":" << location.function_name() << ": "
        << "01 Hello World!" << std::endl;

    log("02 Hello world!");

    auto location2 = std::source_location::current(__FILE__, __FUNCTION__, __LINE__, 0);
    std::cout << location2.file_name() << ":" << location2.line() << ":"
        << location2.column() << ":" << location2.function_name() << ": "
        << "03 Hello World!" << std::endl;

    log("04 Hello world!", std::source_location::current(__FILE__, __FUNCTION__, __LINE__, 0));

    return 0;
}
