package.path = package.path .. ";../?.lua"
package.cpath = package.cpath .. ";../../symcomp/bin/?.so"

local symcomp = require "wsymcomp"

-- test wsymcomp.findintersections
f = symcomp.expr("1/2*x^2")
g = symcomp.expr("x-4")

symcomp.findintersections(f, g, "x")

print("All tests succeeded.")

-- REMOVE

f = symcomp.expr("-3*x**2-4*x**3")

print(symcomp.printzeros(f, "f", "x"))
print(symcomp.printzeros(symcomp.diff(f, "x"), "f'", "x", #symcomp.solve(f, "x")))
print(symcomp.printminmax(f, "f", "x"))