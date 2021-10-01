package.path = package.path .. ";../?.lua"
package.cpath = package.cpath .. ";../wsymengine/bin/?.so"

local symcomp = require "symcomp"
local util = require "util"

-- test symcomp.findintersections
local f = symcomp.expr("x^2")
local g = symcomp.expr("x+2")
local h = symcomp.expr("3")
local k = symcomp.expr("2")

assert(#symcomp.findintersections(f, g, "x") == 2)
assert(#symcomp.findintersections(g, h, "x") == 1)
assert(#symcomp.findintersections(h, k, "x") == 0)

print("All tests succeeded.")