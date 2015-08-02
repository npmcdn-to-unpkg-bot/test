#!/usr/bin/python
#coding:utf-8

import sys

def print_utf8(str):
    print str.decode('utf-8')

s ="""
- module搜索路径 sys.path
  . 主目录
  . PYTHONPATH 目录, 环境变量
  . 标准库目录
  . .pth文件目录

- 第三方工具 distutils
- 命名规范: 模块应以 .py 结尾(但不是必须的)

"""
print_utf8(s)

print sys.path