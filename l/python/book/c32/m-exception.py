#!/usr/bin/python
#coding:utf-8

def fetcher(obj, index):
    return obj[index]

x = 'spam'
fetcher(x, 3)

# 捕捉
try:
    fetcher(x, 4)
except IndexError:
    print 'got exception'

# 引发
try:
    raise IndexError
except IndexError:
    print 'got exception we raised'

# 用户自定义
class Bad(Exception): # Exception is built-in
    pass
def doomed():
    raise Bad()
try:
    doomed()
except Bad:
    print 'got bad'

# 终止行为
try:
    fetcher(x, 3)
finally:
    print 'after fetch' # 乜有异常为进行

try:
    fetcher(x, 4)
finally:
    print 'after try???' # 有异常也会执行,但是也会从这异常退出
