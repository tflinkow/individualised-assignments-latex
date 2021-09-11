#ifndef LIBSYMCOMP_MATHEMATICS_HPP
#define LIBSYMCOMP_MATHEMATICS_HPP

#include <ginac/ginac.h>

#include <symengine/expression.h>
#include <symengine/parser.h>
#include <symengine/solve.h>

//#include <symbolicc++.h>

#include "util.hpp"
#include "exprrep.hpp"

namespace symcomp
{
    symcomp::ExprRep EvaluateAt(const std::string& what, const std::string& var, double value)
    {
        SymEngine::Expression symVar(var);
        auto expression = symcomp::util::StringToSymEngineExpression(what);

        SymEngine::map_basic_basic subsMap;
        subsMap[symVar] = symcomp::util::TryToInt(value);

        auto result = expression.subs(subsMap);

        return symcomp::ExprRep(result);
    }

    std::vector<symcomp::ExprRep> Solve(const std::string& what, const std::string& var)
    {
        auto symVar = SymEngine::make_rcp<SymEngine::Symbol>(var);
        auto expression = symcomp::util::StringToSymEngineExpression(what);

        auto result = SymEngine::solve(expression, symVar)->get_args();

        std::vector<symcomp::ExprRep> solutions;
        solutions.reserve(result.size());

        for(auto const& value : result)
        {
            auto ex = SymEngine::Expression(value);
            auto exprRep = symcomp::ExprRep(ex);

            solutions.push_back(exprRep);
        }
        
        return solutions;
    }

    symcomp::ExprRep Differentiate(const std::string& what, const std::string& var)
    {
        SymEngine::Expression symVar(var);
        auto expression = symcomp::util::StringToSymEngineExpression(what);

        auto derivative = expression.diff(symVar);

        return symcomp::ExprRep(derivative);
    }

    symcomp::ExprRep Integrate(const std::string& what, double lower, double upper, const std::string& var)
    {
        GiNaC::symbol symVar(var);

        GiNaC::symtab table;
        table[var] = symVar;

        GiNaC::parser reader(table);

        auto integrand = reader(what);
        GiNaC::ex expression = GiNaC::integral(symVar, lower, upper, integrand);

        return symcomp::ExprRep(expression.eval_integ());
    }
}

#endif // LIBSYMCOMP_MATHEMATICS_HPP