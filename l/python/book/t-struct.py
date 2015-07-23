#!/usr/bin/python
#coding:utf-8

import struct

# struct 可以解析打包的二进制数据

f = open('data.bin', 'wb')
data = struct.pack('dafei', 7, 'xiaoming', 'xiaoj', 999)
print data
f.write(data)
f.close()