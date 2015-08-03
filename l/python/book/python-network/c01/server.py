#!/usr/bin/python
#coding:utf-8

"""
usage: python server.py

telnet localhost 51423
"""

import socket,sys

host = ''
port = 51423

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((host, port))
s.listen(1)

print 'Sever is running on port %d; press Ctrl+C to terminate.' % port

while True:
    clientsock, clientaddr = s.accept()
    clientfile = clientsock.makefile('rw', 0)
    clientfile.write("Welcome, " + str(clientaddr) + '\n')
    clientfile.write("Please enter a string: ")
    line = clientfile.readline().strip()
    clientfile.write("You enter %d characters.\n" % len(line))
    clientfile.close()
    clientsock.close()