#!/usr/bin/python
#coding:utf-8

def print_out(container):
	print '---container type :', type(container)
	for (offset, item) in enumerate(container):
		print item,'appear at offset ', offset


for s in [
	'spam',
	('a', 'b', 'c'), 
	{'a', 'b', 'c'}, # set是无序的,所以结果有点不是想要的
	['a', 'b', 'c'],
	{"a" :1, "b":2, "c": 4}, # dict是无序的,所以用这个貌似结果不太对
	]:
	print_out(s)