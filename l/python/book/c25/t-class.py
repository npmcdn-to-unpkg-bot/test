#!/usr/bin/python
#coding:utf-8

class C2:
    x = 1
    y = 2
class C3:
    w = 1
    z = 1
class C1(C2, C3):
    def __init__(self, who):
        self.name = who
    def setname(self, who):
        self.name = who

I1 = C1()
I2 = C1()
I1.setname('bob')
I2.setname('mel')
print I1.name, I2.name