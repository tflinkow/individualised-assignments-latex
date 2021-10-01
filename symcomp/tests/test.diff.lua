package.path = package.path .. ";../?.lua"
package.cpath = package.cpath .. ";../wsymengine/bin/?.so"

local symcomp = require "symcomp"
local util = require "util"

-- test symcomp.diff
local f = symcomp.expr("1/2*x^2")
local x = symcomp.expr("x")

local diff = symcomp.diff(f, x)

assert(util.BasicStringFromAny(diff) == "x")

print("All tests succeeded.")