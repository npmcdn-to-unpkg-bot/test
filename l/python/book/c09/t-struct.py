#!/usr/bin/python
#coding:utf-8

import struct

# struct 可以解析打包的二进制数据

f = open('data.bin', 'wb')
data = struct.pack('>i4sh', 7, 'spam', 8) # '>i4sh' 貌似是格式
print data
f.write(data)
f.close()

f = open('data.bin', 'rb')
data = f.read()
print data
values = struct.unpack('>i4sh', data)
print values