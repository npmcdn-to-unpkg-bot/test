#!/usr/bin/python

X = set('spam')
Y = {'h', 'a', 'm'}

print X,Y

print X&Y

print X|Y

print X-Y

print Y-X

print {x**2 for x in [1,2,3,4,5]}