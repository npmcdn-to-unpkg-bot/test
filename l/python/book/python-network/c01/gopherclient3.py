#!/usr/bin/python
#coding:utf-8

"""
usage: gopherclient.py quux.org /
"""

import socket,sys

port = 70
host = sys.argv[1]
filename = sys.argv[2]

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    s.connect((host, port))
# except socket.gaierror, e:
except Exception, e:
    print 'Error connecting to server: %s' % e
    exit(1)

fd = s.makefile('rw', 0) # 0 is buffer size
fd.write(filename + '\r\n')

for line in fd.readlines():
    sys.stdout.write(buf)
