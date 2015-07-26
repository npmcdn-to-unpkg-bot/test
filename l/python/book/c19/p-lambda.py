#!/usr/bin/python
#coding:utf-8

s = """
--------------------------------------------
-  lambda 语法格式
-  lambda arg1, arg2, arg3, ... argN : expression using args
--------------------------------------------
"""
print s.decode('utf-8')

f = lambda x,y,z : x+y+z
print f(1,2,3)

L = [
    lambda x : x ** 2,
    lambda x : x ** 3,
    lambda x : x ** 4
    ]
for f in L:
    print f(2)

def action(x):
    return (lambda y: x+ y)  # rembeber x retuan function
act = action(2)
print act # a function, lambda
print act(66)

# lambda with map
counters = [1,2,3,4,5]
print map((lambda x :x+3), counters)

# filter and reduce
print filter((lambda x: x>0), range(-15, 5))

# reduce 返回单一结果,他需要一个迭代器,把前面的结果传递给下一个元素
print reduce((lambda x,y: x+y), [1,2,3,4,5])