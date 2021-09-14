package.path = package.path .. ";../?.lua"
package.cpath = package.cpath .. ";../../symcomp/bin/?.so"

local symcomp = require "wsymcomp"

-- test wsymcomp.evalAt
f = symcomp.expr("1/2*x^2")
x0 = symcomp.expr("2")

evalAt1 = symcomp.evalAt(basic(f), "x", "2")
evalAt2 = symcomp.evalAt(basic(f), "x", x0)
evalAt3 = symcomp.evalAt(basic(f), "x", 2)

evalAt4 = symcomp.evalAt(f, "x", "2")
evalAt5 = symcomp.evalAt(f, "x", x0)
evalAt6 = symcomp.evalAt(f, "x", 2)

assert(basic(evalAt1) == basic(evalAt2))
assert(basic(evalAt2) == basic(evalAt3))
assert(basic(evalAt3) == basic(evalAt4))
assert(basic(evalAt4) == basic(evalAt5))
assert(basic(evalAt5) == basic(evalAt2))

print("All tests succeeded.")