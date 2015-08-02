#!/usr/bin/python
#coding:utf-8

import sys

x = 'aaa'
print x # 自动加一个换行
print x, # 没有换行

# 打印重定向
sys.stdout.write('Hello World\n')

s = r"print x == sys.stdout.wirte(str(X) + '\n')"
print s

# 让stdout 到文件
tmp = sys.stdout
sys.stdout = open('log.txt', 'a')
print 'Log in file'
sys.stdout.close() # flush output to disk close file
sys.stdout = tmp   # restore stdout