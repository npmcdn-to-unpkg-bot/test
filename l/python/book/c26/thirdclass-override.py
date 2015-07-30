#!/usr/bin/python
#coding:utf-8

s = """
- 以下划线命名的方法 __X__ 是特殊的钩子
- 当实例出现在内置运算时,这类方法会自动调用
  . 例如实例对象继承了 __add__ 方法,出现 + 表达式内这个方法就会调用
- 类可以覆盖多数内置类型运算
- 运算符覆盖方法没有默认值
  . 例如 没有 __add__ 那么 + 表达式就会引发异常 
- 运算符可让类与 python 的对象模型相集成

"""
print s.decode('utf-8')

s = """
----- 这个例子实现 -----
. 构造时候调用__init__
. 出现+ 调用 __add__
. 打印一个对象,内置函数str ,会调用__str__
"""
print s.decode('utf-8')

from secondclass_super_derive import SecondClass
class ThirdClass(SecondClass):
    def __init__(self, value):
        print '__init__ called ...'
        self.data = value
    def __add__(self, other):
        print '__add__ called ...'
        return ThirdClass(self.data + other)
    def __str__(self):
        print '__str__ called ...'
        return '[ThirdClass: %s]' % self.data
    def mul(self, other):
        print 'mul called ...'
        self.data *= other

a = ThirdClass('abc')
a.display()
print a

b = a + 'xyz'
b.display()
print b

a.mul(3)
print a