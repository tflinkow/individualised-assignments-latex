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

local cases = { 5, 50, 500, 5000, 50000 }
local iterations = 10000
local funcs = { { "Lua", random.polynomial }, { "C++", symcomp.debug_randompolynomial } }

for k, v in ipairs(cases) do
    for _, x in ipairs(funcs) do
        print("["..x[1].."] deg(p)="..v.." took "..run(v, x[2], iterations).."s ("..iterations.." iterations)")
    end
end