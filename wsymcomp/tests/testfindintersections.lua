package.path = package.path .. ";../?.lua"
package.cpath = package.cpath .. ";../../symcomp/bin/?.so"

local symcomp = require "wsymcomp"

-- test wsymcomp.findintersections
f = symcomp.expr("1/2*x^2")
g = symcomp.expr("x-4")

symcomp.findintersections(f, g, "x")

print("All tests succeeded.")