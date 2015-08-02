#!/usr/bin/python
#coding:utf-8

s = """
- 列表解析 语法格式
 [expression for target1 in iterable1 [if condition1]
             for target2 in iterable2 [if condition2]
             ...
             for targetN in iterableN [if conditionN]]
"""
print s.decode('utf-8')


print [ x+y for x in [1,2,3] for y in [200,300]]

print [(x,y) for x in range(5) if x%2 == 0
             for y in range(5) if y%2 == 1]

# 列表解析和矩阵

M = [[1,2,3], [4,5,6], [7,8,9]]
N = [[2,2,2], [3,3,3], [4,4,4]]
print [row[1] for row in M]
print [M[row][1] for row in (0,1,2)]

print [M[row][col] * N[row][col] for row in range(3)
                                 for col in range(3)]
# 生成器
def gensquares(N):
    for i in range(N):
        yield i ** 2  # resume here later

for i in gensquares(5):
    print i,   # print last yielded value, like next
print ''

# 生成器表达式: 迭代器遇到列表解析
print [x**2 for x in range(4)] # list-comprehension : build a list

G = (x**2 for x in range(4)) # Generator expression, make an iterable
print G
print next(G)

# 内置类型和类中的值生成
D = {'a':1, 'b':2, 'c':3}
x = iter(D)
print next(x) # 字典每次迭代 key

