#include <iostream>

#include "viennamath/expression.hpp"
#include "viennamath/manipulation/latex.hpp"
#include "viennamath/runtime/numerical_quadrature.hpp"

int main()
{
  viennamath::variable x(0);
  viennamath::latex_translator  to_latex;

  viennamath::numerical_quadrature integrator(new viennamath::gauss_quad_1());

  viennamath::expr integrand = -1/2.0*(x*x) + x + 4;

  viennamath::expr e = viennamath::integral(viennamath::interval(-2.0, 4.0), integrand, x );

  std::cout << to_latex(e) << " = " << integrator(e) << std::endl;
  
  return 0;
}