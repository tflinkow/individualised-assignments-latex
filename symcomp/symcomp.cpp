#include <gsl/gsl>

#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>

#include "exprrep.hpp"
#include "mathematics.hpp"

#define LIBSYMCOMP_LUA_CHECK_PARAMCOUNT(L, n, k) symcomp::util::LuaAssertParamCount(L, #n, k)

#define LIBSYMCOMP_REGISTER_LUAFUNC(n, L, k) static int n(lua_State* (L))\
                                          {\
                                              Expects((L) != nullptr);\
                                              LIBSYMCOMP_LUA_CHECK_PARAMCOUNT(L, n, k);\

#define LIBSYMCOMP_BEGIN_LUAMODULE(n) static const luaL_Reg n[] = {
#define LIBSYMCOMP_LUAMODULE_REGISTER(n) { #n, n }
#define LIBSYMCOMP_END_LUAMODULE { NULL, NULL }  };

extern "C"
{
    LIBSYMCOMP_REGISTER_LUAFUNC(expr, L, 1)

        auto what = luaL_checkstring(L, -1);

        auto result = symcomp::ExprRep(what);

        return result.ReturnToLua(L);
    }

    LIBSYMCOMP_REGISTER_LUAFUNC(evalAt, L, 3)

        auto value = luaL_checknumber(L, -1);        
        auto var = luaL_checkstring(L, -2);
        auto what = luaL_checkstring(L, -3);

        auto result = symcomp::EvaluateAt(what, var, value);

        return result.ReturnToLua(L);
    }

    LIBSYMCOMP_REGISTER_LUAFUNC(solve, L, 2)

        auto var = luaL_checkstring(L, -1);
        auto what = luaL_checkstring(L, -2);

        auto solutions = symcomp::Solve(what, var);

        return symcomp::ReturnExprRepVectorToLua(L, solutions);   
    }

    // subtracts b from a
    // TODO: this does not call into mathematics.hpp!
    LIBSYMCOMP_REGISTER_LUAFUNC(sub, L, 2)

        auto b = luaL_checkstring(L, -1);
        auto a = luaL_checkstring(L, -2);

        auto bEx = symcomp::util::StringToSymEngineExpression(b);
        auto aEx = symcomp::util::StringToSymEngineExpression(a);

        return symcomp::ExprRep(SymEngine::sub(aEx, bEx)).ReturnToLua(L);
    }

    LIBSYMCOMP_REGISTER_LUAFUNC(diff, L, 2)

        auto var = luaL_checkstring(L, -1);
        auto what = luaL_checkstring(L, -2);

        auto result = symcomp::Differentiate(what, var);

        return result.ReturnToLua(L);
    }

    LIBSYMCOMP_REGISTER_LUAFUNC(integrate, L, 4)
        
        auto var = luaL_checkstring(L, -1);
        auto upper = luaL_checknumber(L, -2);
        auto lower = luaL_checknumber(L, -3);
        auto what = luaL_checkstring(L, -4);

        auto result = symcomp::Integrate(what, lower, upper, var);

        return result.ReturnToLua(L);
    }

    LIBSYMCOMP_BEGIN_LUAMODULE(functions)
        LIBSYMCOMP_LUAMODULE_REGISTER(expr),
        LIBSYMCOMP_LUAMODULE_REGISTER(evalAt),
        LIBSYMCOMP_LUAMODULE_REGISTER(solve),
        LIBSYMCOMP_LUAMODULE_REGISTER(sub),
        LIBSYMCOMP_LUAMODULE_REGISTER(diff),
        LIBSYMCOMP_LUAMODULE_REGISTER(integrate),
    LIBSYMCOMP_END_LUAMODULE

[[maybe_unused]] int luaopen_symcomp(lua_State* L)
    {        
        Expects(L != nullptr);
        
        luaL_newlib(L, functions);
        return 1;
    }
}