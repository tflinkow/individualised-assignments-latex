package.path = package.path .. ";../?.lua"

local util = require "util"

-- test exponentiation symbol replacement
local s = "x**2+3^x+4*5"

assert(util.strings.CaretExponent(s) == "x^2+3^x+4*5")
assert(util.strings.AstExponent(s) == "x**2+3**x+4*5")

-- test fraction to number
s = "-1/15"

assert(util.strings.FractionToNumber(s) == -1/15)

print("All tests succeeded.")