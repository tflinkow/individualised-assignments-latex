package.path = package.path .. ";../?.lua"
package.cpath = package.cpath .. ";../../symcomp/bin/?.so"

local symcomp = require "wsymcomp"

-- test wsymcomp.diff
f = symcomp.expr("1/2*x^2")

diff1 = symcomp.diff(basic(f), "x")
diff2 = symcomp.diff(f, "x")

assert(basic(diff1) == basic(diff2))

print("All tests succeeded.")

f = symcomp.expr("-1/2*x**3")
x = symcomp.expr("x")

res = symcomp.diff(f, x)

print(res[1])