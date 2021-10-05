package.path = package.path .. ";../?.lua"
package.cpath = package.cpath .. ";../wsymengine/bin/?.so"

local symcomp = require "symcomp"
local util = require "util"

-- test symcomp.identityMatrix
local A = symcomp.identityMatrix(2)

print(A[1])
print(A[2])

local B = symcomp.matrix("[-2, 1] [12, -3]")

print(B[2])

local detB = symcomp.det(B)

print(detB[2])
