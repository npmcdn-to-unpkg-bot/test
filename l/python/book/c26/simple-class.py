#!/usr/bin/python
#coding:utf-8

class rec : pass
rec.name = 'Bob' # 属于类的,类似static,但是又不共享
rec.age = 40

x = rec()
y = rec()
print rec.name, x.name, y.name 
x.name = 'Sue'
print rec.name, x.name, y.name 

print rec.__dict__.keys()
print x.__dict__.keys()
print y.__dict__.keys()

print x.__class__ # 知道x去哪找
print rec.__bases__

def upperName(obj):
    return obj.name.upper()
print upperName(x)
rec.method = upperName # 类外给类添加个函数
print x.method()
print y.method()
