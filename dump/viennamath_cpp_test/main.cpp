#include <iostream>

#include "viennamath/expression.hpp"
#include "viennamath/manipulation/eval.hpp"
#include "viennamath/manipulation/latex.hpp"
#include "viennamath/manipulation/integrate.hpp"
#include "viennamath/runtime/numerical_quadrature.hpp"

using namespace viennamath;

int main()
{
  // variable x(0);
  // latex_translator  to_latex;

  // expr sq = x * x;

  // std::cout << eval(pow<x, 2>, 4.0) << std::endl;

  // numerical_quadrature integrator(new gauss_quad_1());

  // expr integralexpr = integral(interval(0, 2), (expr) ((x*x) - 15), x );
  // expr result = integrator(integralexpr);

  // std::cout << "Integral: " << to_latex(integralexpr) << std::endl;
  // std::cout << "Solution: " << to_latex(result) << std::endl;

  // viennamath::ct_variable<0> x;  // represents zeroth entry in a vector
  // viennamath::ct_constant<0> c0; // compile time representation of '0'
  // viennamath::ct_constant<1> c1; // compile time representation of '1'
 
  // // integrate x*x over [0,1] with respect to x:
  // std::cout << viennamath::integrate( viennamath::make_interval(c0, c1),
  //                                   x * x,
  //                                   x) << std::endl; //prints 1/3

  // viennamath::variable x(0);
  // viennamath::numerical_quadrature integrator(new viennamath::gauss_quad_1());
  // viennamath::expr intg = viennamath::integral(viennamath::interval(0.0, 1.0), x, x);

  // std::cout << integrator(intg) << std::endl;

  viennamath::variable x(0);
  viennamath::numerical_quadrature integrator(new viennamath::gauss_quad_1());
  auto res = integrator(viennamath::make_interval(0.0, 1.0), x * x, x); 

  std::cout << res << std::endl;

  expr my_integral = integral(interval(0, 1), x * x, x);
  auto res2 = integrator(my_integral); 

  std::cout << res2 << std::endl;
  
  return EXIT_SUCCESS;
}