#!/usr/bin/python
#coding:utf-8

def func(a):
    print a

print func.__name__
print func.func_name
print func.func_code.co_varnames
print func.func_code.co_argcount
# print func.func_dict
# print func.func_code
# print func.func_code
# print func.__str__
# print func.func_globals

# print dir(func)

print dir(func.__code__)
print ''

# func('dafei')

# 可以向函数随意附加任意用户定义的属性
func.dafei = 0
func.dafei += 1
print dir(func)