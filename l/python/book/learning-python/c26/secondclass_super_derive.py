#!/usr/bin/python
#coding:utf-8

s = """
- 超类列在类开头的括号里 class C (C1,C2):
- 类从超类中继承属性
- 实例会继承所有可读取类的属性
  . 寻找变量时,会按照 实例->类->超类(平级 左->右)
- 每个object.attribute都会开启新的独立搜索
- 逻辑的修改是通过修改子类而不是修改超类

"""

print s.decode('utf-8')


import firstclass

class SecondClass(firstclass.FirstClass):
    def display(self):
        print 'Current value = ', self.data
x = firstclass.FirstClass()
x.setdata('aaaa')
z = SecondClass()
z.setdata(42)
z.display()
x.display()