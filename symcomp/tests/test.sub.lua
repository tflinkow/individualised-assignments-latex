package.path = package.path .. ";../?.lua"
package.cpath = package.cpath .. ";../../wsymengine/bin/?.so"

local symcomp = require "symcomp"
local util = require "util"

-- test symcomp.diff
f = symcomp.expr("4*x^2")
g = symcomp.expr("2*x^2")

res = symcomp.sub(f, g)

assert(util.BasicStringFromAny(res) == "2*x**2")

print("All tests succeeded.")