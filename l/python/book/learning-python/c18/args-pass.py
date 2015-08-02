#!/usr/bin/python
#coding:utf-8

s = """

    函数参数匹配表
语法                  位置        解释
fun(value)           调用者  常规参数:通过位置匹配
fun(name=value)      调用者  关键字参数:通过变量名匹配
func(*sequence)      调用者  以name传递所有的对象,并作为独立的基于位置的参数
fun(**dict)          调用者  以name传递所有的key/value,并作为独立的关键字参数
def fun(name)        函数    常规参数:通过位置或者变量名匹配
def fun(name=value)  函数    默认参数值
def fun(*name)       函数    匹配并收集(在元组中)所有包含位置的参数
def fun(**name)      函数    匹配并收集(在字典中)所有包含位置的参数
def fun(*args, name) 函数    参数必须在调用中按照关键字传递
def fun(*,name=value)        python 3.0
"""
print s.decode('utf-8')

def f(a, b, c):
    print a,b,c
# 常规
f(1,2,3)

# 关键字参数
f(1, c =44, b=2)

# 默认参数
def f(a, b=2, c=3):
    print a,b,c
f(1)
f(1,2)

# 关键字和默认参数混合
def func(spam, eggs, toast=0, ham=0):
    print spam,eggs,toast,ham
func(1,2)
func(1, ham=1, eggs=0)
func(spam=1, eggs=0)
func(1,2,3,4)

# 任意参数
print '- 收集参数'.decode('utf-8')
def f(*args):
    print args
f()
f(1)
f(1,2,3,4,'aaa')

# ** 特性类似,但是支队关键字参数有效
def f(**args):
    print args
f()
f(a=1, b=2)

# 混合 实现灵活
def f(a, *pargs, **kargs):
    print a,pargs,kargs
f(1)
f(1,2,3,x=1,y=1)

# 解包参数
def func(a,b,c,d):
    print a,b,c,d
args = (1,2)
args += (3,4)
func(*args)

args = {'a':1, 'b':2, 'c':3}
args['d'] = 4
func(**args)

# 更加灵活的方式
func(1, *(2,3), **{'d' :4})

# 应用函数通用性
def tracer(func, *pargs, **kargs):
    print 'calling:', func.__name__
    return func(*pargs, **kargs)
def func(a,b,c,d):
    print a+b+c+d
tracer(func, 1, 2, c=3, d=4)

# 废弃的apply == *args, **args
# func(*pargs, **kargs) == apply(func, pargs, kargs)
