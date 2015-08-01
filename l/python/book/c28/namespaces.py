#!/usr/bin/python
#coding:utf-8

X = 11 # Global (module) name/attribute (X or namespaces.X)

def f():
    print X # Access global X

def g():
    X = 22 #local variable(X hides module.X)
    print X

def g2():
    global X
    x = 22 # change global in module

class C:
    X = 33 # Class attribute
    def m(self):
        X = 44 # Local variable in method 
        self.X = 55  # Instance atrribute (instance.X)

if __name__ == '__main__':
    print X # 11
    f() # 11
    g() # 22
    print X # 11
    obj = C()
    print obj.X # 33
    obj.m()
    print obj.X # 55
    print C.X # 33
