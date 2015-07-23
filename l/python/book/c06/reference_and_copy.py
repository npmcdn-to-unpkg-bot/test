#!/usr/bin/python

L1 = [1,2,3]
L2 = L1
L1[0] = 22
print L1
print L2 # L2 == L1
print L1 == L2 # True
print L1 is L2 # True

L1 = [1,2,3]
L3 = [1,2,3]
print L1 == L3 # True
print L1 is L3 # False

L1 = [1,2,3]
L2 = L1[:] # make a copy of L1 using slice
L1[0] = 22
print L1
print L2 # L2 != L1

import copy
Y = { "1" : {"a", "b", "c"},
	"2": 3,
	"3": "aa"}
print Y
X = copy.copy(Y)
print X
Z = copy.deepcopy(Y)
print Z

Y["3"] = "cccccc"
print Y
print X
print Z


import sys
print sys.getrefcount(1)
a = "dafei"
print sys.getrefcount(a)

print sys.getrefcount("baichiaaaa")
