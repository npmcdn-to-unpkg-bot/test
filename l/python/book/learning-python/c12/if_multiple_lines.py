#!/usr/bin/python
#coding:utf-8

a = b = c = d = e = f = g = 'a'

# backlashes allow continuations
if a == b and c == d and \
	d == e and f == g:
	print True;

if (a == b and c == d and
	d == e and e == f):
	print True   # A better way


s = ('aaaaa'  # s is a str
	'bbbbbb'
	'ccccc')
print type(s)
print s

# 三元表达式
print 'AAA' if False else 'BBB'