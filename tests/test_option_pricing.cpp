#include <cassert>
#include <cmath>
#include <iostream>

#include "option_pricing.hpp"

int main()
{
    // Test standard normal PDF at 0: n(0) = 1/sqrt(2*pi)
    const double PI = 3.14159265358979323846;
    double pdf0 = n(0.0);
    assert(std::abs(pdf0 - (1.0 / std::sqrt(2.0 * PI))) < 1e-12);

    // Test cumulative normal CDF at 0: N(0) = 0.5
    double cdf0 = N(0.0);
    assert(std::abs(cdf0 - 0.5) < 1e-12);

    // Prepare option data: K=100, T=1, r=0, v=0.2
    OptionData<double> data(100.0, 1.0, 0.0, 0.2);

    // Test call values: price>0, 0<delta<1, gamma>0
    auto call = CallValues(data, 100.0);
    double price = std::get<0>(call);
    double delta = std::get<1>(call);
    double gamma = std::get<2>(call);
    assert(price > 0.0);
    assert(delta > 0.0 && delta < 1.0);
    assert(gamma > 0.0);

    // Test put values: price>0, delta<0, gamma>0
    auto put = PutValues(data, 100.0);
    double price2 = std::get<0>(put);
    double delta2 = std::get<1>(put);
    double gamma2 = std::get<2>(put);
    assert(price2 > 0.0);
    assert(delta2 < 0.0);
    assert(gamma2 > 0.0);

    std::cout << "All unit tests passed." << std::endl;
    return 0;
}