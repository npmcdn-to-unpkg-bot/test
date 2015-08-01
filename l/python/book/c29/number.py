#!/usr/bin/python
#coding:utf-8

class Number:
    def __init__(self, start):
        self.data = start
    def __sub__(self, other):
        return Number(self.data - other)

if __name__ == '__main__':
    x = Number(5)
    y = x - 2
    print y.data