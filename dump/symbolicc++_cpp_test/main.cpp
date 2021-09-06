#include <iostream>
#include "symbolicc++.h"

int main(void)
{
    Symbolic x("x");
    Symbolic integrand = -1/2.0 * Power(x,2) + x + 4 + Sin(x);

    std::cout << integrate(integrand, x, -2, 4);

    return 0;
}