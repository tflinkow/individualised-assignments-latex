#include <gsl/gsl>

#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>

#include "exprrep.hpp"
#include "mathematics.hpp"

#define LIBSYMCOMP_REGISTER_LUAFUNC(n, L, k) static int n(lua_State* (L))\
                                          {\
                                              Expects((L) != nullptr);\
                                              symcomp::util::LuaAssertParamCount(L, #n, k);\

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

    LIBSYMCOMP_REGISTER_LUAFUNC(identityMatrix, L, 1)

        auto size = luaL_checkinteger(L, -1);

        auto matrix = symcomp::IdentityMatrix(size);

        return matrix.ReturnToLua(L);
    }

    LIBSYMCOMP_REGISTER_LUAFUNC(matrix, L, 1)

        auto what = luaL_checkstring(L, -1);

        auto matrix = symcomp::util::DenseMatrixFromString(what);

        auto exprRep = symcomp::ExprRep(*matrix);
        delete matrix;

        return exprRep.ReturnToLua(L);
    }

    LIBSYMCOMP_REGISTER_LUAFUNC(det, L, 1)

        auto what = luaL_checkstring(L, -1);

        auto matrix = symcomp::util::DenseMatrixFromString(what);

        auto det = symcomp::Determinant(*matrix);
        delete matrix;

        return det.ReturnToLua(L);
    }

    LIBSYMCOMP_BEGIN_LUAMODULE(functions)
        LIBSYMCOMP_LUAMODULE_REGISTER(expr),
        LIBSYMCOMP_LUAMODULE_REGISTER(evalAt),
        LIBSYMCOMP_LUAMODULE_REGISTER(solve),
        LIBSYMCOMP_LUAMODULE_REGISTER(sub),
        LIBSYMCOMP_LUAMODULE_REGISTER(diff),
        LIBSYMCOMP_LUAMODULE_REGISTER(identityMatrix),
        LIBSYMCOMP_LUAMODULE_REGISTER(matrix),
        LIBSYMCOMP_LUAMODULE_REGISTER(det),
    LIBSYMCOMP_END_LUAMODULE

[[maybe_unused]] int luaopen_wsymengine(lua_State* L)
    {        
        Expects(L != nullptr);
        
        luaL_newlib(L, functions);
        return 1;
    }
}
