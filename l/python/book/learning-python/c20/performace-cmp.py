#!/usr/bin/python
#coding:utf-8

import time

reps = 10000
repslist = range(reps)

def timer(func, *pargs, **kargs):
    start = time.clock()
    for i in repslist:
        ret = func(*pargs, **kargs)
    elapsed = time.clock() - start
    return (elapsed, ret)

def forloop():
    res = []
    for x in repslist:
        res.append(abs(x))
    return res

def listcomp():
    return [abs(x) for x in repslist]

def mapcall():
    return list(map(abs, repslist))

def genexpr():
    return list(abs(x) for x in repslist)

def genFunc():
    def gen():
        for x in repslist:
            yield abs(x)
    return list(gen())

for test in (forloop, listcomp, mapcall, genexpr, genFunc):
    elapsed, result = timer(test)
    print '-' * 33
    print '%-9s: %.5f => [%s...%s]' % (test.__name__, elapsed, result[0], result[-1])

