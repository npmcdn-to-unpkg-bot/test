#!/usr/bin/python
#coding:utf-8

def mysum(L):
    return L[0] if len(L) == 1 else L[0] + mysum(L[1:])

print mysum([1,2,3,4,5,6])

# 循环VS递归
# python 使用循环更加的自然
# 除了一些循环处理不了的情况

# 求下面的数字的和
L = [1, [2, [3, 4], 5], 6, [7, 8]]
def sumtree(L):
    tot = 0
    for x in L:
        if not isinstance(x, list):
            tot += x
        else:
            tot += sumtree(x)
    return tot
print sumtree(L)
