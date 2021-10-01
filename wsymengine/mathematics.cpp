#include "mathematics.hpp"

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

    symcomp::ExprRepCollection realSolutions;
    realSolutions.reserve(solutions.size());

    // sort in ascending order, e.g. x0 = -2, x1 = 4, x2 = 10
    std::sort(solutions.begin(), solutions.end(), SymEngine::RCPBasicKeyLess());
    std::reverse(solutions.begin(), solutions.end());

    for (auto solution : solutions)
    {
        if(SymEngine::is_true(SymEngine::is_real(*solution)))
        {
            auto ex = SymEngine::Expression(solution);
            auto exprRep = symcomp::ExprRep(ex);

            realSolutions.push_back(exprRep);
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
