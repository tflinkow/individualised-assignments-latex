package.cpath = package.cpath .. ";../symcomp/bin/?.so"
local symcomp = require "wsymcomp"

-- test wsymcomp.integrate
f = symcomp.expr("1/2*x^2")
l = symcomp.expr("0")
u = symcomp.expr("3")

integrate1 = symcomp.integrate(basic(f), basic(l), basic(u), "x")
integrate2 = symcomp.integrate(basic(f), basic(l), u, "x")
integrate3 = symcomp.integrate(basic(f), basic(l), tonumber(basic(u)), "x")

integrate4 = symcomp.integrate(basic(f), basic(l), basic(u), "x")
integrate5 = symcomp.integrate(basic(f), l, u, "x")
integrate6 = symcomp.integrate(basic(f), tonumber(basic(l)), tonumber(basic(u)), "x")

integrate7 = symcomp.integrate(f, basic(l), basic(u), "x")
integrate8 = symcomp.integrate(f, l, u, "x")
integrate9 = symcomp.integrate(f, tonumber(basic(l)), tonumber(basic(u)), "x")

integrate10 = symcomp.integrate(f, basic(l), basic(u), "x")
integrate11 = symcomp.integrate(f, l, u, "x")
integrate12 = symcomp.integrate(f, tonumber(basic(l)), tonumber(basic(u)), "x")

assert(basic(integrate1) == basic(integrate2))
assert(basic(integrate2) == basic(integrate3))
assert(basic(integrate3) == basic(integrate4))
assert(basic(integrate4) == basic(integrate5))
assert(basic(integrate5) == basic(integrate6))
assert(basic(integrate6) == basic(integrate7))
assert(basic(integrate7) == basic(integrate8))
assert(basic(integrate8) == basic(integrate9))
assert(basic(integrate9) == basic(integrate10))
assert(basic(integrate10) == basic(integrate11))
assert(basic(integrate11) == basic(integrate12))

print("All tests succeeded.")