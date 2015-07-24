#!/usr/bin/python
#coding:utf-8

# * 剩下的内容可以匹配带星号的名称
# python 3.0
seq = [x for x in range(0, 5)]

a,b,c,*d = seq
print a,b,c,d