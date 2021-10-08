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

TEST_CASE("IdentityMatrix correctly creates identity matrix")
{
    CHECK(symcomp::IdentityMatrix(2).Basic == "[1.0, 0.0] [0.0, 1.0]");
    CHECK(symcomp::IdentityMatrix(3).Basic == "[1.0, 0.0, 0.0] [0.0, 1.0, 0.0] [0.0, 0.0, 1.0]");
}

TEST_CASE("MatrixFromString correctly parses matrices")
{
    auto expected = "[12, 13.5] [x, -4]";
    auto matrix = symcomp::util::DenseMatrixFromString("[12,13.5][x,-4]");

    auto exprRep = symcomp::ExprRep(*matrix);

    CHECK(exprRep.Basic == expected);
}

TEST_CASE("Determinant correctly calculates the determinant")
{
    CHECK(symcomp::Determinant("[4, 8] [10, 2]").Basic == "-72");
}

TEST_CASE("MultiplyMatrixByScalar correctly multiplies matrix elements with the scalar")
{
    auto matrix = "[4, 8] [10, 2]";
    auto scalar = "lambda";

    CHECK(symcomp::MultiplyMatrixByScalar(scalar, matrix).Basic == "[4*lambda, 8*lambda] [10*lambda, 2*lambda]");
}

TEST_CASE("SubMatrices correctly subtracts one matrix from another")
{
    auto a = "[4, 8] [10, 2]";
    auto b = "[8, 2] [4, 7]";

    CHECK(symcomp::SubMatrices(a, b).Basic == "[-4.0, 6.0] [6.0, -5.0]");
}

TEST_CASE("Eigenvalues correctly calculates eigenvalues")
{
    auto eigenvalues = symcomp::Eigenvalues("[4, 8] [10, 2]");

    CHECK(eigenvalues.size() == 2); // count
    CHECK(eigenvalues[0].Basic == "-6"); // order
    CHECK(eigenvalues[1].Basic == "12"); // order
}