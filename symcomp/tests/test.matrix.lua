package.path = package.path .. ";../?.lua"
package.cpath = package.cpath .. ";../wsymengine/bin/?.so"

local symcomp = require "symcomp"
local util = require "util"

-- test symcomp.identityMatrix
local A = symcomp.identityMatrix(2)

--assert(util.BasicStringFromAny(A) == "[1, 0] [0, 1]")
print(util.BasicStringFromAny(A))

-- test symcomp.matrix
local B = symcomp.matrix("[-2, 1] [12, -3]")

--assert(util.BasicStringFromAny(B) == "[-2, 1] [12, -3]")
print(util.LaTeXStringFromAny(B))

-- test symcomp.det
local detB = symcomp.det(B)

--assert(util.BasicStringFromAny(detB) == "-6")
print(util.BasicStringFromAny(detB))

-- test symcomp.scalarMul
local C = symcomp.scalarMul(4, B)

--assert(util.BasicStringFromAny(C) == "[-8, 4] [48, -12]")
print(util.BasicStringFromAny(C))

-- test symcomp.matrixSub
local D = symcomp.matrix("[5, 2] [3, -4]")
local E = symcomp.matrix("[1, 2] [3, 4]")

local F = symcomp.matrixSub(D, E)

--assert(util.BasicStringFromAny(F) == "[4, 0] [0, -8]")
print(util.BasicStringFromAny(F))

-- test symcomp.eigenvalues
local G = symcomp.matrix("[-2, 1] [12, -3]")

local eigenvalues = symcomp.eigenvalues(G)

print(eigenvalues[1])
print(eigenvalues[2])

print(symcomp.printeigenvalues(G, "G"))
