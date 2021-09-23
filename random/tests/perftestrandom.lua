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

local cases = { 3, 5, 8, 10, 50, 100, 500 }
local iterations = 10000
local funcs = { { "Lua", random.polynomial }, { "C++", symcomp.debug_randompolynomial } }

for k, v in ipairs(cases) do
    for _, x in ipairs(funcs) do
    	res = run(v, x[2], iterations)
        print("["..x[1].."] deg(p)="..v.." took "..res.."s ("..iterations.." iterations = "..(res/iterations).."s per call)")
    end
end
