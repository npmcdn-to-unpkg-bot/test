#!/usr/bin/python
#coding:utf-8

"""
"""

import gopherlib, sys

host = 'quux.org'
file = '/'

f = gopherlib.send_selector(file, host)
for line in f.readlines():
    sys.stdout.write(line)

