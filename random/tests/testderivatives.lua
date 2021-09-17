package.path = package.path .. ";../../wsymcomp/?.lua;../?.lua"
package.cpath = package.cpath .. ";../../symcomp/bin/?.so"

local random = require "random"
local symcomp = require "wsymcomp"

local factory = 
    {
        { "a", random.integer() },
        { "b", random.integer() }
    }

    random.create("a*x**3+b*x**2", factory)

    -- if f(x)=a*x^3+b*x^2 we can ensure that
    -- f has zero x=0 (multiplicity 2)
    -- f has zero x=b/a (multiplicity 1)
    f = symcomp.expr(random.create("a*x**3+b*x**2", factory))

    d1 = symcomp.diff(f, "x")
    d2 = symcomp.diff(d1, "x")
    d3 = symcomp.diff(d2, "x")

    -- TODO: zeros, min, max, inflections?
    fzeros = symcomp.solve(f, "x")

    print(f[1])
    print(#fzeros)
    print(fzeros[1][1])
    print(fzeros[2][1])