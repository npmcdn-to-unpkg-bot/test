#!/usr/bin/python
#coding:utf-8

"""
usage: *.py 'this is ascii' '这是一个中文的'

"""

import sys

class D:
    def __init__(self, asscii, non_ascii):
        self.ascii_str = asscii
        self.nonascii_str = non_ascii

    def __repr__(self):
        # 不知道为啥这样也可以,不过如果不可以,用下面的方法
        return '<D asscii:{}, non-ascii:{}'.format(self.ascii_str, self.nonascii_str)

# 当用 __repr__ 返回值有非 ascii 的时候,
# 在2.x版本,貌似你只能这样, 注意前面是用 u 来让他变为 unicode
# def __repr__(self)
#    return u'<A {}'.format(self.non-ascii-data).encode('utf-8)

# 输出的时候呢,要显示调用 repr()

# print repr(d).decode('utf-8)

if __name__ == '__main__':
    # print sys.argv

    d = D(sys.argv[1], sys.argv[2])
    print d