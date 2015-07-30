#!/usr/bin/python
#coding:utf-8

class FirstClass:
    def setdata(self, value):
        self.data = value
    def display(self):
        print self.data

x = FirstClass()
y = FirstClass()

print dir(FirstClass) # ['__doc__', '__module__', 'display', 'setdata']
print dir(x) # ['__doc__', '__module__', 'display', 'setdata']
x.setdata(11)
print dir(FirstClass) # ['__doc__', '__module__', 'display', 'setdata']
print dir(x) # ['__doc__', '__module__', 'data', display', 'setdata']
s ='- data属性会在 实例 中找到,但是  setdata 和 display 是在他们的类中找到的'
print s.decode('utf-8')

# 可以类外新增属性
x.newatrr = 'this is a new attr'
print dir(x) # print dir(x) # ['__doc__', '__module__', 'data', display', 'setdata']

