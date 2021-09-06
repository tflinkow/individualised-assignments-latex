#include <iostream>
#include <ginac/ginac.h>

std::vector<std::string> integral_eval(double llim, double ulim, const char* integrand)
{
    GiNaC::symbol x("x");
    GiNaC::symtab table;
    table["x"] = x;
    GiNaC::parser reader(table);
    GiNaC::ex p = reader(integrand);

    GiNaC::ex e = GiNaC::integral(x, llim, ulim, p);

    const char** returnValue = new const char*[2];

    std::vector<std::string> vec;

    std::ostringstream oss;
    oss << GiNaC::latex << e;

    vec.push_back(std::string(oss.str()));

    std::ostringstream os2;
    os2 << GiNaC::latex << e.eval_integ();

    vec.push_back(std::string(os2.str()));
    
    return vec;
}

extern "C"
{
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>

    static int integral(lua_State* L)
    {
        double ulim = lua_tonumber(L, -1);
        double llim = lua_tonumber(L, -2);
        const char* integrand = lua_tostring(L, -3);

        auto ret = integral_eval(llim, ulim, integrand);

        const char* returnValue1 = ret[0].c_str();
        const char* returnValue2 = ret[1].c_str();

        lua_pushstring(L, returnValue1);
        lua_pushstring(L, returnValue2);

        return 2;
    }

    static const luaL_Reg functions[] =
    {
        { "integral", integral },
        { NULL, NULL }
    };

    int luaopen_main(lua_State* L)
    {
        luaL_newlib(L, functions);

        return 1;
    }
}