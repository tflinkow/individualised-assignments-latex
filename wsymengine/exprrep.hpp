#ifndef LIBSYMCOMP_EXPRREP_HPP
#define LIBSYMCOMP_EXPRREP_HPP

#include <symengine/expression.h>
#include <symengine/parser.h>

#include <gsl/gsl>

#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>

#include <string>
#include <sstream>

#include "util.hpp"

namespace symcomp
{
    class ExprRep
    {
    public:
        std::string Basic;
        std::string LaTeX;

        ExprRep() = default;

        ExprRep(std::string basic, std::string laTeX);
        explicit ExprRep(const std::string& basic);

        explicit ExprRep(const SymEngine::Expression& expression);

        int ReturnToLua(gsl::not_null<lua_State*> L) const;
    };

    typedef std::vector<symcomp::ExprRep> ExprRepCollection;

    int ReturnExprRepVectorToLua(gsl::not_null<lua_State*> L, const ExprRepCollection& collection);
}

#endif // LIBSYMCOMP_EXPRREP_HPP
