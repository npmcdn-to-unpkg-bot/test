#!/usr/bin/python
#coding:utf-8

# a  append
# w  write
# r  read
# +  同时读写

f = open('test.txt', 'w')
f.write('Line 1\n')
f.write('Line 2\n')
lines_list = ['line 3\n', 'line 4']
f.writelines(lines_list)
f.flush()
f.close()
f = open('test.txt') # default is r
whole = f.read()
print whole
f.close()

f = open('test.txt')
whole = f.read(10)
print whole

f.seek(0)
lines = f.readlines()
print lines

f.seek(0)
line = f.readline()
print line

f.seek(0)
for line in f:
	print line,
