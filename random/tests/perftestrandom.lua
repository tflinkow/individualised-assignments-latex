package.path = package.path .. ";../../wsymcomp/?.lua;../?.lua"
package.cpath = package.cpath .. ";../../symcomp/bin/?.so"

local random = require "random"
local symcomp = require "symcomp"

function run(deg, func, iterations)
    start = os.clock()

    for i=1, iterations do
        func(deg)
    end

    return os.clock() - start
end

local cases = { 3,6,10,30,60,100,200,400 }
local iterations = 10000
local funcs = { { "Lua", random.polynomial }, { "C++", symcomp.debug_randompolynomial } }

local lua = {}
local cpp = {}

for k, v in ipairs(cases) do
    for c, x in ipairs(funcs) do
    	res = run(v, x[2], iterations)
        
        if c == 1 then
            lua[#lua+1] = {v, res/iterations}
        else
            cpp[#cpp+1] = {v, res/iterations}
        end

        print("["..x[1].."] deg(p)="..v.." took "..res.."s ("..iterations.." iterations = "..(res/iterations).."s per call)")
    end
end

print("=Lua=")

for k, v in ipairs(lua) do
    print("(" .. v[1] .. ", " .. v[2] .. ")")
end

print("=C++=")

for k, v in ipairs(cpp) do
    print("(" .. v[1] .. ", " .. v[2] .. ")")
end