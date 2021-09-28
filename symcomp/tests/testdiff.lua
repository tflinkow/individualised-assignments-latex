package.path = package.path .. ";../?.lua"
package.cpath = package.cpath .. ";../../wsymengine/bin/?.so"

local symcomp = require "symcomp"
local util = require "util"

f = symcomp.expr("-1/2*x**3")
xi = symcomp.expr("x")

function run(func, iterations)
    start = os.clock()

    for i=1, iterations do
        func(f, xi)
    end

    return os.clock() - start
end

local iterations = 10000
local funcs = { { "SymEngine", symcomp.diff }, { "symmath", symcomp.diff2 } }

local lua = {}
local cpp = {}


res = run(funcs[1][2], iterations)
print("["..funcs[1][1].."] took "..res.."s ("..iterations.." iterations = "..(res/iterations).."s per call)")

res = run(funcs[2][2], iterations)
print("["..funcs[2][1].."] took "..res.."s ("..iterations.." iterations = "..(res/iterations).."s per call)")