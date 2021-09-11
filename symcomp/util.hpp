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
    // Creates a SymEngine::Expression by parsing the supplied string.
    inline SymEngine::Expression StringToSymEngineExpression(const std::string& str)
    {
        return {SymEngine::parse(str) };
    }

    // Returns a SymEngine::Integer if the specified value is a whole number (such as 4.0 or 7.0) and SymEngine::Number otherwise.
    inline SymEngine::RCP<const SymEngine::Number> TryToInt(double a)
    {
        // https://stackoverflow.com/a/26343165/7571171
        if(std::fmod(a, static_cast<decltype(a)>(1.0)) == 0.0)
        {
            return SymEngine::integer(static_cast<int>(a));
        }
        
        return SymEngine::number(a);
    }

    // Checks whether the Lua function was called with the specified number of parameters and calls luaL_error if it was not.
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