#!/usr/bin/python
#coding:utf-8

import SimpleHTTPServer
import SocketServer

PORT = 8000
handler = SimpleHTTPServer.SimpleHTTPRequestHandler
httpd = SocketServer.TCPServer(("", PORT), handler)

print "servering at port ", PORT
httpd.serve_forever()