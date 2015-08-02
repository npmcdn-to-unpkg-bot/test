#!/usr/bin/python
#coding:utf-8

s = """
- 使用包导入,每个目录必须有 __init__.py 这个文件,否则失败
   . import dir1.dir2.mod
   . dir1/dir2/mod.py
   . dir1和dir2必须都有一个__init__.py

"""

print s.decode('utf-8')

import dir1.dir2.mod
from dir1.dir2 import mod

print dir1
print dir1.dir2
print dir1.dir2.mod
print dir1.x,dir1.dir2.y,dir1.dir2.mod.z
print mod.z