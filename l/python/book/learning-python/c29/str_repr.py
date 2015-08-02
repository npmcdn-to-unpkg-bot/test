#!/usr/bin/python
#coding:utf-8

class Adder:
    def __init__(self, value=0):
        self.data = value
    def __add__(self, other):
        self.data += other
    def __repr__(self):
        return 'add-repr(%s)' % self.data
    def __str__(self):
        return 'add-str(%s)' % self.data
x = Adder()
print x
print repr(x)