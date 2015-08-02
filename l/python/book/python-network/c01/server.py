#!/usr/bin/python
#coding:utf-8

"""
usage:
"""

import socket,sys

host = ''
port = 51423

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((host, port))
s.lenten(1)

print 'Sever is running on port %d; press Ctrl+C to terminate.' % port
