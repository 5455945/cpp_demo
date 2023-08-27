#include "01-04.h"

#include <stacktrace>
#include <string>
#include <iostream>

void test04_01() {
  auto trace = std::stacktrace::current();
  std::cout << std::to_string(trace) << '\n';
}

void test04()
{
    auto st = std::stacktrace::current();
    std::cout <<
        "Description of an empty stacktrace entry:\n" +
        std::to_string(std::stacktrace_entry{}) << '\n';
    if (st.size() > 0) {
        std::cout <<
            "Description of a non-empty stacktrace entry:\n" +
            std::to_string(st[0]) << '\n';
    }
}


