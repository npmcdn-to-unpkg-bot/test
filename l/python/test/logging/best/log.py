#!/usr/bin/python
#coding:utf-8

import app

"""
app/main/module: app.main.module
app/main/__init__: app.main
app/module: app.module
app/__init__: app
This is the main show__name__: __main__

所以说,logging用 __name__ 是再合适不过了,
只要初始化一个root(以__name__),其他的子模块都可以
自动用 app.xxx.xx 作为日志
"""

if __name__ == '__main__':
    print 'This is the main show__name__:', __name__
    app.log()