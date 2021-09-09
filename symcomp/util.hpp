#ifndef LIBSYMCOMP_UTIL_HPP
#define LIBSYMCOMP_UTIL_HPP

#include <symengine/expression.h>
#include <symengine/parser.h>

#include <string>

namespace symcomp::util
{
    SymEngine::Expression StringToSymEngineExpression(const std::string& str)
    {
        return SymEngine::Expression(SymEngine::parse(str));
    }
}

#endif // LIBSYMCOMP_UTIL_HPP