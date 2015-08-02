#!/usr/bin/python
#coding:utf-8

import namespaces

X = 66 # the global here
print X
print namespaces.X

namespaces.f()
namespaces.g()

print namespaces.C.X
i = namespaces.C()
print i.X
i.m()
print i.X