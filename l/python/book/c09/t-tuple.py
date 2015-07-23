#!/usr/bin/python
#coding:utf-8

# 不能在原处修改

print ()
print (0,)
print (0, 'Ni', 1, 2, 3,)
T = 0, 'Ni', 1, 2, 3,
print T
T = ('abc', ('def', 'ghi'),)
print T
print tuple('spam')
print T[0]
print T[1][0]
print T[0:2]
print len(T)
T2 = ('c', 'd')
print T + T2
print T * 3
for x in T : print x
print [x*2 for x in T]
print T.index('abc')
print T.count('abc')

X = (40) # 数字
print X
X =(40,) # tuple
print X