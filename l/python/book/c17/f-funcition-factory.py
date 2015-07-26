#!/usr/bin/python
#coding:utf-8

def factory(N):
    def action(X):
        return X ** N
    return action

fun = factory(2)
print fun
print fun(3)
print fun(4)