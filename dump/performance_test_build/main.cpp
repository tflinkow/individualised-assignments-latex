#include <ginac/ginac.h>

#include <symengine/expression.h>
#include <symengine/parser.h>

#include "symbolicc++.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

namespace SymComp
{
    SymEngine::Expression ParseFrom(std::string s)
    {
        return SymEngine::Expression(SymEngine::parse(s));
    }

    class ExprRep
    {
        public:
            std::string BasicRep;
            std::string LaTeX;

            ExprRep(std::string& basicRep, std::string& laTeX) : BasicRep(basicRep), LaTeX(laTeX)
            {                
            }

            ExprRep(SymEngine::Expression expr)
            {
                std::ostringstream oss;
                oss << expr;

                this->BasicRep = oss.str();

                oss.str("");
                oss.clear();

                oss << latex(expr);

                this->LaTeX = oss.str();
            }

            // TODO: Also a constructor for SymbolicC++ etc.

            ExprRep(GiNaC::ex expr)
            {
                std::ostringstream oss;
                oss << expr;

                *this = ExprRep(SymComp::ParseFrom(oss.str()));
            }
    };

    int ExprRepToLua(lua_State* L, const ExprRep& exprRep)
    {
        lua_newtable(L); // now table is at -1
        lua_pushstring(L, exprRep.BasicRep.c_str()); // now string is at -1, table at -2
        lua_rawseti(L, -2, 1);
        lua_pushstring(L, exprRep.LaTeX.c_str());
        lua_rawseti(L, -2, 2);

        return 1; // one return value (a table)
    }

    // Derivates expression by symVar
    // e.g. expression = 7*x^2 and symVar = x -> returns 14*x
    SymComp::ExprRep Derivate(const std::string& expression, const std::string& symVar)
    {
        std::cout << "=[DEBUG]= Derivating " << expression << " with respect to " << symVar << std::endl;

        SymEngine::Expression var(symVar);
        auto ex = SymComp::ParseFrom(expression);

        auto res = ex.diff(var);

        return SymComp::ExprRep(res);
    }

    // Calculates the definite integral of the expression
    SymComp::ExprRep Integrate(const std::string& what, double limitLower, double limitUpper, const std::string& symVar)
    {
        std::cout << "=[DEBUG]= Integrating " << what << " from " << limitLower << " to " << limitUpper << " with respect to " << symVar << std::endl;
        
        GiNaC::symbol var(symVar);

        GiNaC::symtab table;
        table[symVar] = var;
        GiNaC::parser reader(table);

        GiNaC::ex e = GiNaC::integral(var, limitLower, limitUpper, reader(what));

        return SymComp::ExprRep(e.eval_integ());
    }
}

#define EXTERN_LUA_FUNC(n) static int n(lua_State* L)
#define LUA_MODULE_FUNC(n) { #n, n }
#define LUA_MODULE_SENTINEL { NULL, NULL }

extern "C"
{
    EXTERN_LUA_FUNC(derivate)
    {
        auto symVar = std::string(lua_tostring(L, -1));
        auto expr = std::string(lua_tostring(L, -2));

        auto res = SymComp::Derivate(expr, symVar);

        return SymComp::ExprRepToLua(L, res);
    }

    EXTERN_LUA_FUNC(integrate)
    {
        auto symVar = std::string(lua_tostring(L, -1));
        auto upperLimit = lua_tonumber(L, -2);
        auto lowerLimit = lua_tonumber(L, -3);
        auto expr = std::string(lua_tostring(L, -4));

        auto res = SymComp::Integrate(expr, lowerLimit, upperLimit, symVar);

        return SymComp::ExprRepToLua(L, res);
    }

    static const luaL_Reg functions[] =
    {
        LUA_MODULE_FUNC(derivate),
        LUA_MODULE_FUNC(integrate),
        LUA_MODULE_SENTINEL
    };

    int luaopen_main(lua_State* L)
    {
        luaL_newlib(L, functions);
        return 1;
    }
}