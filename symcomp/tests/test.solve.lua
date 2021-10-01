package.path = package.path .. ";../?.lua"
package.cpath = package.cpath .. ";../wsymengine/bin/?.so"

local symcomp = require "symcomp"
local util = require "util"

-- test symcomp.evalAt
local f = symcomp.expr("-x^2+4")
local x = symcomp.expr("x")

local res = symcomp.solve(f, x)

assert(#res == 2)
assert(util.BasicStringFromAny(res[1]) == "-2")
assert(util.BasicStringFromAny(res[2]) == "2")

print("All tests succeeded.")