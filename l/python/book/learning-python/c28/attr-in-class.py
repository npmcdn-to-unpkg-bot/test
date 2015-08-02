#!/usr/bin/python
#coding:utf-8

class SharedData:
    spam = 42
    def __init__(self):
        self.a = 'a'
        self.b = 'b'

x = SharedData()
y = SharedData()
print x.spam, y.spam, SharedData.spam
x.spam = 88 # 对对象属性修改时候,总是会修改对象,不会影响class
# 这句会让 spam 附加在x本身上
print x.spam, y.spam, SharedData.spam

SharedData.spam = 99
print x.spam, y.spam, SharedData.spam

print dir(x)
print dir(y)

class MixedNames:
    data = 'spam'
    def __init__(self, value):
        self.data = value
    def display(self):
        print self.data,MixedNames.data
x = MixedNames(1)
y = MixedNames(2)
x.display()
y.display()
# data 存在于2个地方.在实例对象内(__init__中的self.data)
# 以及在实例继承变量名的类中(类中的data赋值运算所创建)

s = """
-------------------------------
 instance.method(args..)
 ==>
 class.method(instance, args...)
 跟c++ 一样哦
-------------------------------
"""
print s.decode('utf-8')

class NextClass:
    def printer(self, text):
        self.message = text
        print self.message
x = NextClass()
x.printer('instance call')
print x.message
NextClass.printer(x, 'instance call 2')
print x.message

# 通过超类构造函数
class Super:
    def __init__(self, x):
        self.a = 'a'

class Sub(Super):
    def __init__(self, x, y):
        Super.__init__(self,x)
        self.y = y
I = Sub(1,2)
