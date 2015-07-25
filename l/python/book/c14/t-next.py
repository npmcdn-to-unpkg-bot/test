#!/usr/bin/python
#coding:utf-8

print r'next(X) == x.__next__()'

f = open('data.txt', 'r')
# print f.__next__() # 
print next(f)
print next(f)
print next(f)
print next(f)