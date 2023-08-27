#include "01-05.h"

#include <iostream>

void test05() {
    auto gcd = [](this auto self, int a, int b) -> int {
        return b == 0 ? a : self(b, a % b);
    };

    std::cout << gcd(20, 30) << "\n";
}

