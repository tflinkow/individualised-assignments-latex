package.path = package.path .. ";../?.lua"

local util = require "util"

-- test exprrep member access
ex = { "Foo", "Bar" }

assert(util.exprrep.Basic(ex) == "Foo")
assert(util.exprrep.LaTeX(ex) == "Bar")

-- test BasicStringFromAny
ex = { "Foo", "Bar" }

assert(util.BasicStringFromAny(ex) == "Foo")
assert(util.BasicStringFromAny(ex[1]) == "Foo")
assert(util.BasicStringFromAny(42) == "42")

-- test LaTeXStringFromAny
ex = { "Foo", "Bar" }

assert(util.LaTeXStringFromAny(ex) == "Bar")
assert(util.LaTeXStringFromAny(ex[2]) == "Bar")
assert(util.LaTeXStringFromAny(42) == "42")

-- test NumberFromAny
ex = { "42", "1/2" }

assert(util.NumberFromAny(ex) == 42)
assert(util.NumberFromAny(ex[1]) == 42)
assert(util.NumberFromAny(ex[2]) == 0.5)
assert(util.NumberFromAny(42) == 42)

print("All tests succeeded.")