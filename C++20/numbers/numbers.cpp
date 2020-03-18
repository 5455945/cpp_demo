#include <numbers>
#include <iostream>

void test_numbers01() {
    std::cout << "std::numbers::e: " << std::numbers::e << " " << std::numbers::e_v<double> << std::endl;
    std::cout << "std::numbers::log2e: " << std::numbers::log2e << " " << std::numbers::log2e_v<double> << std::endl;
    std::cout << "std::numbers::log10e: " << std::numbers::log10e << " " << std::numbers::log10e_v<double> << std::endl;
    std::cout << "std::numbers::pi: " << std::numbers::pi << " " << std::numbers::pi_v<double> << std::endl;
    std::cout << "std::numbers::inv_pi: " << std::numbers::inv_pi << " " << std::numbers::inv_pi_v<double> << std::endl;
    std::cout << "std::numbers::inv_sqrtpi: " << std::numbers::inv_sqrtpi << " " << std::numbers::inv_sqrtpi_v<double> << std::endl;
    std::cout << "std::numbers::ln2: " << std::numbers::ln2 << " " << std::numbers::ln2_v<double> << std::endl;
    std::cout << "std::numbers::ln10: " << std::numbers::ln10 << " " << std::numbers::ln10_v<double> << std::endl;
    std::cout << "std::numbers::sqrt2: " << std::numbers::sqrt2 << " " << std::numbers::sqrt2_v<double> << std::endl;
    std::cout << "std::numbers::sqrt3: " << std::numbers::sqrt3 << " " << std::numbers::sqrt3_v<double> << std::endl;
    std::cout << "std::numbers::inv_sqrt3: " << std::numbers::inv_sqrt3 << " " << std::numbers::inv_sqrt3_v<double> << std::endl;
    std::cout << "std::numbers::egamma: " << std::numbers::egamma << " " << std::numbers::egamma_v<double> << std::endl;
    std::cout << "std::numbers::phi: " << std::numbers::phi << " " << std::numbers::phi_v<double> << std::endl;
    std::cout << "std::numbers::e: " << std::numbers::e << " " << std::numbers::e_v<double> << std::endl;
}

int main() {
    test_numbers01();
    return 0;
}
