package.cpath = package.cpath .. ";../symcomp/bin/?.so"
local symcomp = require "wsymcomp"

-- test wsymcomp.solve
f = symcomp.expr("-x+4")

solve1 = symcomp.solve(basic(f), "x")[1]
solve2 = symcomp.solve(f, "x")[1]

assert(basic(solve1) == basic(solve2))

print("All tests succeeded.")