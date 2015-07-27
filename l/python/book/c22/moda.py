#!/usr/bin/python
#coding:utf-8

X = 88
def f():
    global X # Change this file's X
    X = 99 # Cannot see names in other modules, 不会改变其他文件的名字为X的变量
    
