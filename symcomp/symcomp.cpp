#include <gsl/gsl>

#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>

#include "exprrep.hpp"
#include "mathematics.hpp"

#define LIBSYMCOMP_REGISTER_LUAFUNC(n, L) static int n(lua_State* L)
#define LIBSYMCOMP_BEGIN_LUAMODULE(n) static const luaL_Reg n[] = {
#define LIBSYMCOMP_LUAMODULE_REGISTER(n) { #n, n }
#define LIBSYMCOMP_END_LUAMODULE { NULL, NULL }  };

extern "C"
{
    LIBSYMCOMP_REGISTER_LUAFUNC(expression, L)
    {        
        Expects(L != nullptr);

        auto what = lua_tostring(L, -1);

        auto result = symcomp::ExprRep(what);

        return result.ReturnToLua(L);
    }

    LIBSYMCOMP_REGISTER_LUAFUNC(derivate, L)
    {        
        Expects(L != nullptr);

        auto var = lua_tostring(L, -1);
        auto what = lua_tostring(L, -2);

        auto result = symcomp::Derivate(what, var);

        return result.ReturnToLua(L);
    }

    LIBSYMCOMP_REGISTER_LUAFUNC(integrate, L)
    {        
        Expects(L != nullptr);
        
        auto var = lua_tostring(L, -1);
        auto upper = lua_tonumber(L, -2); // TODO: checknumber?
        auto lower = lua_tonumber(L, -3);
        auto what = lua_tostring(L, -4);

        auto result = symcomp::Integrate(what, lower, upper, var);

        return result.ReturnToLua(L);
    }

    LIBSYMCOMP_BEGIN_LUAMODULE(functions)
        LIBSYMCOMP_LUAMODULE_REGISTER(expression),
        LIBSYMCOMP_LUAMODULE_REGISTER(derivate),
        LIBSYMCOMP_LUAMODULE_REGISTER(integrate),
    LIBSYMCOMP_END_LUAMODULE

    int luaopen_symcomp(lua_State* L)
    {        
        Expects(L != nullptr);
        
        luaL_newlib(L, functions);
        return 1;
    }
}