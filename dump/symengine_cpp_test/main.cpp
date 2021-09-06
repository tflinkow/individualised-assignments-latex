#include <symengine/expression.h>
#include <symengine/parser.h>
#include <iostream>

using SymEngine::Expression;

SymEngine::Expression ParseFrom(std::string s)
{
    return SymEngine::Expression(SymEngine::parse(s));
}

int main()
{
    SymEngine::print_stack_on_segfault();

    SymEngine::Expression x("x");

    auto expr = 3 * SymEngine::pow(x, 4) + SymEngine::sin(x);
    auto result = expr.diff(x);

    std::cout << SymEngine::latex(result) << std::endl;

    std::string p = "-1/2*x**2+x+4+sin(x)";

    auto ex = ::ParseFrom(p);

    auto differ = ex.diff(x);

    std::cout << latex(differ) << std::endl;    

    return 0;
}