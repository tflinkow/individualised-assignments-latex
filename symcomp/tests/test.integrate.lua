package.path = package.path .. ";../?.lua"
package.cpath = package.cpath .. ";../../wsymengine/bin/?.so"

local symcomp = require "symcomp"
local util = require "util"

-- test symcomp.integrate(f, x, l, u)
f = symcomp.expr("1/2*x^2")

res = symcomp.integrate(f, "x", 0, 6)

assert(util.BasicStringFromAny(res) == "36")

-- test symcomp.integrate(f, x)
--f = symcomp.expr("1/3*x^2")

--res = symcomp.integrate(f, "x")

-- TODO
--assert(util.BasicStringFromAny(res) == "36")

print("All tests succeeded.")

res = symcomp.integrate("x+4-1/2*x^2", "x")

print(util.BasicStringFromAny(res))

-- TODO: symcomp.simplify schaffen!
res = symcomp.expr(symcomp.integrate("x+4-1/2*x^2", "x")[1])

print(util.BasicStringFromAny(res))