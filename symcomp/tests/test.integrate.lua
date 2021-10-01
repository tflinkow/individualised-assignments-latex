package.path = package.path .. ";../?.lua"
package.cpath = package.cpath .. ";../../wsymengine/bin/?.so"

local symcomp = require "symcomp"
local util = require "util"

-- test symcomp.integrate(f, x, l, u)
f = symcomp.expr("1/2*x^2")

res = symcomp.integrate(f, "x", 0, 6)

assert(util.BasicStringFromAny(res) == "36")

-- test symcomp.integrate(f, x)
f = symcomp.expr("1/3*x^2")

res = symcomp.integrate(f, "x")

assert(util.BasicStringFromAny(res) == "(x ^ 3) / 9")

print("All tests succeeded.")