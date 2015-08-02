#!/usr/bin/python
#coding:utf-8

print 'Use zip to get a list with pair'
L1 = [1,2,3,4]
L2 = [5,6,7,8,9,0]
print L1
print L2
# zip two list
print zip(L1, L2)

# get a dict
print dict(zip(L1,L2))

# zip more than one list
print zip(L1, L1, L1, L2)
