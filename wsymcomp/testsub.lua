package.cpath = package.cpath .. ";../symcomp/bin/?.so"
local symcomp = require "wsymcomp"

-- test wsymcomp.sub
f = symcomp.expr("1/2*x^2")
g = symcomp.expr("x+4")

sub1 = symcomp.sub(basic(f), basic(g))
sub2 = symcomp.sub(basic(f), g)

sub3 = symcomp.sub(f, basic(g))
sub4 = symcomp.sub(f, g)

assert(basic(sub1) == basic(sub2))
assert(basic(sub2) == basic(sub3))
assert(basic(sub3) == basic(sub4))

print("All tests succeeded.")