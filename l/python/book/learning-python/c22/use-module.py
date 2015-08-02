#!/usr/bin/python
#coding:utf-8

import module1
from module1 import printer
from module2 import *
module1.printer('Use import')
printer('Use form import')
printer2('Use form import *')


import import_multiple
print import_multiple.spam
import_multiple.spam = 33
import import_multiple # the old one, won't load again
print import_multiple.spam
reload(import_multiple) # reload
print import_multiple.spam


s = """
- 模块语句会在首次导入时候执行
- 顶层的赋值语句会创建模块属性.
   * 不在 def和class之内的赋值语句,例如 =和def *
- 模块的命名空间能通过属性__dict__ 或者 dir(M) 获取
- 模块是一个独立的作用域(本地变量就是全局变量)

- reload 会在模块当前命名空间内执行模块文件的新建
- 文件中顶层赋值语句会使变量化成新值
- 重载会印象所有使用import读取了模块的客户端
- 重载只会对以后使用from的客户端造成影响
"""
print s.decode('utf-8')

import module3
print module3.sys
print module3.name
print module3.func
print module3.kclass

print module3.__dict__.keys()
print '-' * 30
print module3.__dict__['name'] # 42
print module3.__dict__['__name__'] #__name__ module3
# __file__  D:\dev\repo\test\l\python\book\c22\module3.pyc
print module3.__dict__['__file__'] 


X = 11
import moda
moda.f()
print X,moda.X