#!/usr/bin/python

def fun1():
	print "This is fun1"

def fun2():
	print "This is fun2"

all = (
	("01", fun1),
	("02", fun2)
	)

for item in range(len(all)):
	print "index:{}, v:{}".format(item,all[item][0])
	all[item][1]()

print "Map way..."
for item in map(None, all):
	print item
	print item[0]
	item[1]()