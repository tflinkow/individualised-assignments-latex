package.path = package.path .. ";../?.lua"
package.cpath = package.cpath .. ";../../wsymengine/bin/?.so"

local symcomp = require "symcomp"
local util = require "util"

-- test symcomp.diff
f = symcomp.expr("1/2*x^2")
x = symcomp.expr("x")

diff = symcomp.diff(f, x)

assert(util.BasicStringFromAny(diff) == "x")

print("All tests succeeded.")