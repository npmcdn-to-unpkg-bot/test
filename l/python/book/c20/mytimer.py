#!/usr/bin/python
#coding:utf-8

import time
import sys

if sys.platform[:3] == 'win':
    timefunc = time.clock # good on windows
else:
    timefunc = time.time  # better on unix platforms

def trace(*args): pass

def timer(func, *pargs, **kargs):
    _reps = kargs.pop('_reps', 1000) # Passed-in or default _reps
    trace(func, pargs, kargs, _reps)
    repslist = range(_reps)
    start = timefunc()
    for i in repslist:
        ret = func(*pargs, **kargs)
    elapsed  = timefunc() - start
    return (elapsed, ret)
