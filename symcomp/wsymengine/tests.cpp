#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest.h>

#include "exprrep.hpp"
#include "mathematics.hpp"

TEST_CASE("ExprRep(string, string) correctly sets members")
{
    auto basic = "basic";
    auto latex = "latex";

    auto exprRep = symcomp::ExprRep(basic, latex);

    CHECK(exprRep.Basic == basic);
    CHECK(exprRep.LaTeX == latex);
}

TEST_CASE("ExprRep(string) generates LaTeX representation and correctly sets members")
{
    auto basic = "1/2";

    auto exprRep = symcomp::ExprRep(basic);

    CHECK(exprRep.Basic == basic);
    CHECK(exprRep.LaTeX == "\\frac{1}{2}");
}

TEST_CASE("EvaluateAt evaluates the function at x0 correctly")
{
    auto f = "x^2";
    auto x = "x";

    CHECK(symcomp::EvaluateAt(f, x, 2).Basic == "4");
    CHECK(symcomp::EvaluateAt(f, x, 4).Basic == "16");
    CHECK(symcomp::EvaluateAt(f, x, 4.0).Basic == "16");
}

TEST_CASE("Solve correctly solves an equation")
{
    auto f = "x^2-4";
    auto x = "x";

    auto solutions = symcomp::Solve(f, x);

    CHECK(solutions.size() == 2); // count
    CHECK(solutions[0].Basic == "-2"); // order
    CHECK(solutions[1].Basic == "2"); // order
}

TEST_CASE("Differentiate correctly calculates derivative")
{
    auto f = "x^3+x";
    auto x = "x";

    CHECK(symcomp::Differentiate(f, x).Basic == "1 + 3*x**2");
}
