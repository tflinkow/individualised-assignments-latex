package.path = package.path .. ";../?.lua"
package.cpath = package.cpath .. ";../wsymengine/bin/?.so"

local symcomp = require "symcomp"
local util = require "util"

-- test symcomp.evalAt
local f = symcomp.expr("1/2*x^2")
local x = symcomp.expr("x")

local res = symcomp.evalAt(f, x, 2)

assert(util.BasicStringFromAny(res) == "2")

print("All tests succeeded.")