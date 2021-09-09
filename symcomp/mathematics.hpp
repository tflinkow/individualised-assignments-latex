#ifndef LIBSYMCOMP_MATHEMATICS_HPP
#define LIBSYMCOMP_MATHEMATICS_HPP

#include <ginac/ginac.h>

#include <symengine/expression.h>
#include <symengine/parser.h>

#include <symbolicc++.h>

#include "util.hpp"
#include "exprrep.hpp"

namespace symcomp
{
    symcomp::ExprRep Derivate(const std::string& what, const std::string& var)
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