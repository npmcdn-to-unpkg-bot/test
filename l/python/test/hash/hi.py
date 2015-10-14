#!/usr/bin/python
#coding:utf-8

"""

http://www.cnblogs.com/BeginMan/p/3328172.html

"""

import hashlib

m = hashlib.md5()
m.update('dafei')

print m.digest()    #返回摘要，作为二进制数据字符串值
print m.hexdigest() #返回十六进制数字字符串    aec06d3a087d87bc6bb4521f170768ce
print m.digest_size #16
print m.block_size  #64