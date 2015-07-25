#!/usr/bin/python
#coding:utf-8

x = 0
while x < 10:
	print x,
	x += 1
print ''

for x in list('spam'):
	print x

for (a,b) in [(1,2), (3,4), (5,6)]:
	print a,b

print r"for didn't have for (int i=0; i<10;i++) like c++"
print "Use for i in range(0,10) altinative"

# use zip ,按照最短的来,map是按照最长的用none补齐
L1 = [1,2,3,4]
L2 = [5,6,7,8,9]
print zip(L1,L2)
for (x,y) in zip(L1, L2):
	print x,y,'--',x+y
# map是按照最长的用none补齐
print map(None, L1, L2)
for (x,y) in map(None, L1, L2):
	print x,y
