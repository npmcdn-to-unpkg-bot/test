#!/usr/bin/python
#coding:utf-8

class A:
    def __init__(self, data):
        self.data = data
    def add(self, c):
        self.data += c
    def __repr__(self):
        return self.data


def do_something(f):
    def wrapper():
        a = A('do_something1')
        print 'At first, a:', a
        f(a)
        print 'At last, a:', a

    return wrapper


@do_something
def printa(a):
    print 'In printa, a:',a
    a.add("1:I change this string")


if __name__ == '__main__':
    printa()
