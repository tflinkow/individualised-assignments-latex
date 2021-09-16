package.path = package.path .. ";../wsymcomp/?.lua"
package.cpath = package.cpath .. ";../symcomp/bin/?.so"

local random = require "random"
local symcomp = require "wsymcomp"

local factory = 
{
    { "a", random.rational() },
    { "b", random.integer(4, 10) },
    { "n", random.integer(1, 3) }
}

ex = symcomp.expr(random.create("a*x**n+b", factory))
print(ex[1])

parabola = symcomp.expr(random.parabola()) -- random.parabola(b) works too where b can be anything
print(parabola[1])

line = symcomp.expr(random.line())
print(line[1])

polynomial = symcomp.expr(random.polynomial(4))
print(polynomial[1])
