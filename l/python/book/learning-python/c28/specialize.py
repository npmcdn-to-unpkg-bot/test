#!/usr/bin/python
#coding:utf-8

class Super:
    def method(self):
        print 'in Super.method'
    def delegate(self):
        self.action()
    def action(self):
        assert False, 'action must be defined!'

class Inheritor(Super):
    pass

class Replacer(Super):
    def method(self):
        print 'In Replacer.method'

class Extender(Super):
    def method(self):
        print 'starting Extender.method'
        Super.method(self)
        print 'ending Extender.method'

class Provider(Super):
    def action(self):
        print 'in Provider.action'

if __name__ == '__main__':
    for kclass in (Inheritor, Replacer, Extender):
        print '\n' + kclass.__name__ + '...'
        kclass().method() #  必须实例化,所以 kclass()
    print '\nProvider...'
    x = Provider()
    x.delegate()

    y = Super()
    y.delegate() # assert

s = """
- 简单变量名, 如果赋值就不是全局变量
  . 赋值语句 X = value
    使变量名成为本地变量.在当前作用域内,创建或者改变变量名X
    除非生命他是 全局变量
"""
print s.decode('utf-8')