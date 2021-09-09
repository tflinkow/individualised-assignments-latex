#ifndef LIBSYMCOMP_EXPRREP_HPP
#define LIBSYMCOMP_EXPRREP_HPP

#include <ginac/ginac.h>

#include <symengine/expression.h>
#include <symengine/parser.h>

#include <symbolicc++.h>

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

        ExprRep(std::string& basic, std::string& laTeX) : Basic(basic), LaTeX(laTeX)
        {
        }

        ExprRep(std::string& basic)
        {
            *this = ExprRep(symcomp::util::StringToSymEngineExpression(basic));
        }

        ExprRep(SymEngine::Expression expression)
        {
            std::ostringstream oss;
            oss << expression;

            auto basic = oss.str();

            oss.str("");
            oss.clear();

            oss << SymEngine::latex(expression);

            auto laTeX = oss.str();

            *this = ExprRep(basic, laTeX);
        }

        ExprRep(GiNaC::ex expression)
        {
            std::ostringstream oss;
            oss << expression;

            *this = ExprRep(oss.str());
        }

        // TODO: also for SymbolicC++

        int ReturnToLua(lua_State* L)
        {
            lua_pushstring(L, this->Basic.c_str());
            lua_pushstring(L, this->LaTeX.c_str());
            
            return 2;
        
            lua_newtable(L); // table @-1
            lua_pushstring(L, this->Basic.c_str()); // table @-2, string @-1
            lua_rawseti(L, -2, 1); // basic is table[1]
            lua_pushstring(L, this->LaTeX.c_str()); // table @-2, string @-1
            lua_rawseti(L, -2, 2); // laTeX is table[2]

            return 1; // one return value (a table)
        }
    };
}

#endif // LIBSYMCOMP_EXPRREP_HPP
