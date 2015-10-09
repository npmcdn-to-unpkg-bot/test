#!/usr/bin/python
#coding:utf-8

# CHILD class is still instance of super class
class A(object):
    def __init__(self):
        self.data = "this is a"

    def p(self):
        print 'This is A'

class B(A):
    def __init__(self):
        self.data = "This is b"
    def p(self):
        super(B, self).p()
        print 'This is also B'

if __name__ == '__main__':
    a = A()
    b = B()
    if isinstance(a, A):
        print 'a is instance of A'

    if isinstance(b, A):
        print 'b is instance of A'
    else:
        print 'b is NOT instance of A'

    b.p()