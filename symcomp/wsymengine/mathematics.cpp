#include "mathematics.hpp"

#include <symengine/matrix.h>
#include <symengine/solve.h>

symcomp::ExprRep symcomp::EvaluateAt(const std::string &what, const std::string &var, double value)
{
    SymEngine::Expression symVar(var);
    auto expression = symcomp::util::StringToSymEngineExpression(what);

    SymEngine::map_basic_basic subsMap;
    subsMap[symVar] = symcomp::util::TryToInt(value);

    auto result = expression.subs(subsMap);

    return symcomp::ExprRep(result);
}

symcomp::ExprRepCollection symcomp::Solve(const std::string &what, const std::string &var)
{
    auto symVar = SymEngine::symbol(var);
    auto expression = symcomp::util::StringToSymEngineExpression(what);

    // workaround, because below code does not work:
    //auto solutions = SymEngine::solve(expression, symVar, SymEngine::reals());
    // see https://github.com/symengine/symengine/issues/1843

    auto solutions = SymEngine::solve(expression, symVar)->get_args();

    ExprRepCollection realSolutions;
    realSolutions.reserve(solutions.size());

    // sort in ascending order, e.g. x0 = -2, x1 = 4, x2 = 10
    std::sort(solutions.begin(), solutions.end(), SymEngine::RCPBasicKeyLess());
    std::reverse(solutions.begin(), solutions.end());

    for (const auto& solution : solutions)
    {
        // does not work, see https://github.com/symengine/symengine/issues/1843#issuecomment-932520001
        //if(SymEngine::is_true(SymEngine::is_real(*solution)))

        // workaround: check whether eval_double throws
        try
        {
            SymEngine::eval_double(*solution);

            // success: real solution
            auto ex = SymEngine::Expression(solution);
            auto exprRep = symcomp::ExprRep(ex);

            realSolutions.push_back(exprRep);
        }
        catch (const SymEngine::SymEngineException&)
        {
            // do nothing, complex solution
        }
    }

    return realSolutions;
}

symcomp::ExprRep symcomp::Differentiate(const std::string &what, const std::string &var)
{
    SymEngine::Expression symVar(var);
    auto expression = symcomp::util::StringToSymEngineExpression(what);

    auto derivative = expression.diff(symVar);

    return symcomp::ExprRep(derivative);
}

symcomp::ExprRep symcomp::IdentityMatrix(int size) {

    auto matrix = SymEngine::DenseMatrix(size, size);

    for (int i = 0; i < matrix.nrows(); ++i)
    {
        for (int j = 0; j < matrix.ncols(); ++j)
        {
            matrix.set(i, j, i == j ? SymEngine::number(1) : SymEngine::number(0));
        }
    }

    return symcomp::ExprRep(matrix);
}

symcomp::ExprRep symcomp::Determinant(const SymEngine::MatrixBase &matrix)
{
    return symcomp::ExprRep(matrix.det());
}
