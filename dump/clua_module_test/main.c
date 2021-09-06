#include <lua.h>     /* Always include this */
#include <lauxlib.h> /* Always include this */
#include <lualib.h>  /* Always include this */

static int iadd(lua_State* L)
{                
	int a = (int) lua_tonumber(L, -1);
	int b = (int) lua_tonumber(L, -2);

    int result = a + b;
	
	lua_pushnumber(L, result);
	
	return 1;
}

static int ifortytwo(lua_State* L)
{
    lua_pushnumber(L, 42);

    return 1;
}

static int iglobal(lua_State* L)
{
    lua_pushnumber(L, 10);

    return 1;
}

static const luaL_Reg functions[] = 
{
    // { "<function name in Lua>", <actual c function> }
    { "add", iadd },
    { "theAnswer", ifortytwo },
    { NULL, NULL } // sentinel entry, this MUST be present at the end (see http://www.lua.org/manual/5.3/manual.html#luaL_Reg)
};

// The .so file must be called "example_module" then
int luaopen_module(lua_State *L)
{
    // Option 1: defining all functions globally using lua_register(L, "<function name in lua>", <actual c function>)
	//lua_register(L, "add", iadd);
    //lua_register(L, "theAnswer", ifortytwo);
    lua_register(L, "globalFunction", iglobal);

    // Option 2: defining a new table (i.e. module) using luaL_newlib(L, <array of c functions>)
    // see also: http://www.lua.org/manual/5.3/manual.html#luaL_newlib
    luaL_newlib(L, functions);
	
    // Return the number of module(s) returned (I believe, I have not found documentation for this)
	return 1;
}