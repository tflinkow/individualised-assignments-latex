#include <cstdlib>
#include <iostream>
#include <vector>
#include <ginac/ginac.h>

int main()
{
    GiNaC::symbol x("x");

    const int DEG_UPPER = 10;
    const int COEF_UPPER = 20;

    int maxDeg = std::rand() % DEG_UPPER; // inclusive

    std::cout << "maxDeg = " << maxDeg << std::endl;

    std::vector<int> coefficients;
    std::vector<int> powers;

    // Generate a polynom \sum\limits_{i = 0}^{maxDeg} a_i * x^i
    for (int i = 0; i <= maxDeg; i++)
    {
        coefficients.push_back(std::rand() % COEF_UPPER);
        powers.push_back(maxDeg - i);
    }

    GiNaC::ex e = 0;

    for (int i = 0; i <= maxDeg; i++)
    {
        std::cout << "coef[" << i << "] = " << coefficients[i] << " pow[" << i << "] = " << powers[i] << std::endl;
        e += coefficients[i] * GiNaC::pow(x, powers[i]);
    }
    
    std::cout << e << std::endl;

    return 0;
}