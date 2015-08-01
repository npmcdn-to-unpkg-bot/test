#!/usr/bin/python
#coding:utf-8

class super:
    def hello(self):
        self.data1 = 'spam'

class sub(super):
    def hola(self):
        self.data2 = 'eggs'
x = sub()
print x.__dict__ # empty now
print x.__class__ # sub
print sub.__bases__ # super class

x.hello()
print x.__dict__ # not empty {'data':'spam'}
x.hola()
print x.__dict__ # not empty {'data':'spam', 'data2':'eggs'}

print x.data1, x.__dict__['data1']
x.data3 = 'toast'
print x.__dict__
x.__dict__['data3'] = 'ham'
print x.__dict__

print sub.__dict__.keys()
print super.__dict__.keys()

s = """
继承的属性不能通过__dict__来读取
例如 x.hello 不能通过  x.__dict__['hello'] 读取
"""
print s.decode('utf-8')