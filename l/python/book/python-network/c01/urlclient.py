#!/usr/bin/python
#coding:utf-8

import urllib, sys

f = urllib.urlopen('gopher://' + 'quux.org' + '/')

while 1:
    buf = f.read(2048)
    if not len(buf):
        break
    sys.stdout.write(buf)