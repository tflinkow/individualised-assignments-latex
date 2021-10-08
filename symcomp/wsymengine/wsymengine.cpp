#include <gsl/gsl>

#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>

#include "exprrep.hpp"
#include "mathematics.hpp"

#define LIBSYMCOMP_EXPOSE_TO_LUA(n, L, k) static int n(lua_State* (L))\
                                          {\
                                              Expects((L) != nullptr);\
                                              symcomp::util::LuaAssertParamCount(L, #n, k);\

#define LIBSYMCOMP_BEGIN_LUAMODULE(n) static const luaL_Reg n[] = {
#define LIBSYMCOMP_ADD_TO_LUAMODULE(n) { #n, n }
#define LIBSYMCOMP_END_LUAMODULE { NULL, NULL }  };

extern "C"
{
    LIBSYMCOMP_EXPOSE_TO_LUA(expr, L, 1)

        auto what = luaL_checkstring(L, -1);

        auto result = symcomp::ExprRep(what);

        return result.ReturnToLua(L);
    }

    LIBSYMCOMP_EXPOSE_TO_LUA(evalAt, L, 3)

        auto value = luaL_checknumber(L, -1);        
        auto var = luaL_checkstring(L, -2);
        auto what = luaL_checkstring(L, -3);

        auto result = symcomp::EvaluateAt(what, var, value);

        return result.ReturnToLua(L);
    }

    LIBSYMCOMP_EXPOSE_TO_LUA(solve, L, 2)

        auto var = luaL_checkstring(L, -1);
        auto what = luaL_checkstring(L, -2);

        auto solutions = symcomp::Solve(what, var);

        return symcomp::ReturnExprRepVectorToLua(L, solutions);   
    }

    // subtracts b from a
    LIBSYMCOMP_EXPOSE_TO_LUA(sub, L, 2)

        auto b = luaL_checkstring(L, -1);
        auto a = luaL_checkstring(L, -2);

        auto bEx = symcomp::util::StringToSymEngineExpression(b);
        auto aEx = symcomp::util::StringToSymEngineExpression(a);

        return symcomp::ExprRep(SymEngine::sub(aEx, bEx)).ReturnToLua(L);
    }

    LIBSYMCOMP_EXPOSE_TO_LUA(diff, L, 2)

        auto var = luaL_checkstring(L, -1);
        auto what = luaL_checkstring(L, -2);

        auto result = symcomp::Differentiate(what, var);

        return result.ReturnToLua(L);
    }

    LIBSYMCOMP_EXPOSE_TO_LUA(identityMatrix, L, 1)

        auto size = luaL_checkinteger(L, -1);

        auto matrix = symcomp::IdentityMatrix(size);

        return matrix.ReturnToLua(L);
    }

    LIBSYMCOMP_EXPOSE_TO_LUA(matrix, L, 1)

        auto what = luaL_checkstring(L, -1);

        auto matrix = symcomp::util::DenseMatrixFromString(what);

        return symcomp::ExprRep(*matrix).ReturnToLua(L);
    }

    LIBSYMCOMP_EXPOSE_TO_LUA(det, L, 1)

        auto what = luaL_checkstring(L, -1);

        return symcomp::Determinant(what).ReturnToLua(L);
    }

    LIBSYMCOMP_EXPOSE_TO_LUA(scalarMul, L, 2)

        auto matrix = luaL_checkstring(L, -1);
        auto scalar = luaL_checkstring(L, -2);

        auto result = symcomp::MultiplyMatrixByScalar(scalar, matrix);

        return result.ReturnToLua(L);
    }

    LIBSYMCOMP_EXPOSE_TO_LUA(matrixSub, L, 2)

        auto B = luaL_checkstring(L, -1);
        auto A = luaL_checkstring(L, -2);

        auto result = symcomp::SubMatrices(A, B);

        return result.ReturnToLua(L);
    }

    LIBSYMCOMP_EXPOSE_TO_LUA(eigenvalues, L, 1)

        auto what = luaL_checkstring(L, -1);

        return symcomp::ReturnExprRepVectorToLua(L, symcomp::Eigenvalues(what));
    }

    LIBSYMCOMP_BEGIN_LUAMODULE(functions)
                    LIBSYMCOMP_ADD_TO_LUAMODULE(expr),
                    LIBSYMCOMP_ADD_TO_LUAMODULE(evalAt),
                    LIBSYMCOMP_ADD_TO_LUAMODULE(solve),
                    LIBSYMCOMP_ADD_TO_LUAMODULE(sub),
                    LIBSYMCOMP_ADD_TO_LUAMODULE(diff),
                    LIBSYMCOMP_ADD_TO_LUAMODULE(identityMatrix),
                    LIBSYMCOMP_ADD_TO_LUAMODULE(matrix),
                    LIBSYMCOMP_ADD_TO_LUAMODULE(det),
                    LIBSYMCOMP_ADD_TO_LUAMODULE(scalarMul),
                    LIBSYMCOMP_ADD_TO_LUAMODULE(matrixSub),
                    LIBSYMCOMP_ADD_TO_LUAMODULE(eigenvalues),
    LIBSYMCOMP_END_LUAMODULE

[[maybe_unused]] int luaopen_wsymengine(lua_State* L)
    {        
        Expects(L != nullptr);
        
        luaL_newlib(L, functions);
        return 1;
    }
}
