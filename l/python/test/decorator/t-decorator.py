#!/usr/bin/python
#coding:utf-8


import time

def foo():
    print 'in foo()'

# 定义一个计时器，传入一个，并返回另一个附加了计时功能的方法
def timeit(func):

    # 定义一个内嵌的包装函数，给传入的函数加上计时功能的包装
    def wrapper():
        start = time.clock()
        func()
        end =time.clock()
        print 'used:', end - start

    # 将包装后的函数返回
    return wrapper

foo = timeit(foo)
foo()

# python中提供了一个@符号的语法糖，用来简化上面的代码，他们的作用一样
# 这2段的代码是一样的，等价的
@timeit
def foo2():
    print 'In foo2()'

foo2()
