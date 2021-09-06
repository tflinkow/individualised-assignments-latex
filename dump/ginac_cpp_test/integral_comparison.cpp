#include <iostream>
#include <ginac/ginac.h>

int main()
{
  GiNaC::symbol x("x");
  GiNaC::ex integrand = -1/2.0 * GiNaC::pow(x, 2) + x + 4;
  GiNaC::ex e = GiNaC::integral(x, -2, 4, integrand);

  std::cout << GiNaC::latex 
            << e << " = " << e.eval_integ() 
            << std::endl;

  return 0;
}