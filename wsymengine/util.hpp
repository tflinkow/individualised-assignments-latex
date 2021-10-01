#ifndef LIBSYMCOMP_UTIL_HPP
#define LIBSYMCOMP_UTIL_HPP

#include <symengine/expression.h>
#include <symengine/parser.h>

#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
#include <lua5.3/lauxlib.h>

#include <cmath>
#include <string>

#define LOG(msg) std::cout << msg << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl

namespace symcomp::util
{
    /// Creates a \c SymEngine::Expression from the specified string \p str.
    /// \param str The string containing a mathematical expression.
    /// \return A \c SymEngine::Expression.
    inline SymEngine::Expression StringToSymEngineExpression(const std::string& str)
    {
        return { SymEngine::parse(str) };
    }

    /// Returns a \c SymEngine::Integer if the specified value is a whole number (e.g. 4.0 or 7.0) and returns a
    /// \c SymEngine::Number otherwise.
    /// \param a The number.
    /// \return A \c SymEngine::Number which might be a \c SymEngine::Integer.
    inline SymEngine::RCP<const SymEngine::Number> TryToInt(double a)
    {
        // https://stackoverflow.com/a/26343165/7571171
        if (std::fmod(a, static_cast<decltype(a)>(1.0)) == 0.0)
        {
            return SymEngine::integer(static_cast<int>(a));
        }
        
        return SymEngine::number(a);
    }

    /// Throws an error if the Lua function \p function was not called with the expected number of parameters.
    /// \param L The Lua stack.
    /// \param function The function called.
    /// \param expected The expected number of parameters.
    inline void LuaAssertParamCount(lua_State* L, const std::string& function, int expected)
    {
        auto actual = lua_gettop(L);

        if (actual != expected) [[unlikely]]
        {
            std::ostringstream oss;
            oss << "function '" << function << "' expected " << expected << " parameters, got " << actual;

            luaL_error(L, oss.str().c_str());
        }
    }
}

#endif // LIBSYMCOMP_UTIL_HPP
