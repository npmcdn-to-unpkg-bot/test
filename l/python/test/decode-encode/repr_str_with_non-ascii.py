#!/usr/bin/python
# coding:utf-8


"""
usage: *.py 'this is ascii' '这是一个中文的'
 linux default encoding is utf-8
 so
  'this is ascii' will be encoded as utf-8, the same as ascii.
  '这是一个中文的' should be utf-8



要统一 encoding
1. # coding:utf-8
2. 所有的 unicode 是转化为字符串的时候都 encode('utf-8)

"""

import logging
import sys
import chardet

class D:
    def __init__(self, asscii, non_ascii):
        self.input_ascii_str = asscii # 'this is ascii'   utf-8/ascii the same, because there is only  ascii
        self.input_nonascii_str = non_ascii # '这是一个中文的' , utf-8
        self.ascii_str = 'an origin ascii' # ascii == utf-8
        self.unicode_str = u'来让他变为 unicode' # unicode object
        self.utf8_str = '原始的字符串,应该是utf-8编码的' # utf-8

    def print_info(self, name, value):
        """
        unicode object can't be detect in chardet.detect, only use str
        """
        encoding = chardet.detect(value)
        print '{} type: {}, encoding: {}'.format(name, type(value), encoding.get('encoding'))

    def __repr__(self):

        print '-' * 50
        self.print_info('input_ascii_str', self.ascii_str)
        self.print_info('input_nonascii_str', self.input_nonascii_str)
        self.print_info('ascii_str', self.ascii_str)
        # self.print_info('unicode_str', self.unicode_str) # unicode object can't use chardet.detect
        self.print_info('utf8_str', self.utf8_str)
        print '-' * 50

        # ascii can be encode to unicode, so this is OK to use u or not
        print '<D input_ascii_str:{}'.format(self.input_ascii_str)
        print u'<D input_ascii_str:{}'.format(self.input_ascii_str)
        print '<D asscii:{}'.format(self.ascii_str)
        print u'<D asscii:{}'.format(self.ascii_str)

        # this works because utf-8 is type str
        print '<D asscii:{}'.format(self.input_nonascii_str) 
        print '<D asscii:{}'.format(self.utf8_str)

        # this didn't work

        print '-' * 50

        utf8 = 'utf-8 print\ninput_ascii_str:{}\ninput_nonascii_str:{}\nascii_str:{}\nunicode_str:{}\nutf8_str:{}'.format(
                self.input_ascii_str,
                self.input_nonascii_str,
                self.ascii_str,
                self.unicode_str.encode('utf-8'), # need to use utf-8 because others are all utf-8
                self.utf8_str)
        print utf8

        unic = u'unicode print\ninput_ascii_str:{}\ninput_nonascii_str:{}\nascii_str:{}\nunicode_str:{}\nutf8_str:{}'.format(
                self.input_ascii_str, # can implict convert to unicode
                self.input_nonascii_str.decode('utf-8'),  # utf-8 need explict convert to unicode
                self.ascii_str, # can implict convert to unicode
                self.unicode_str,
                self.utf8_str.decode('utf-8')) # utf-8 need explict convert to unicode
        print '-' * 50
        print  unic
        print '-' * 50

        # you can't return an unicode object directly.
        # it will try to convert the unicode object to str type.
        # so you need return an utf-8 string.
        return unic.encode('utf-8')


# 当用 __repr__ 返回值有非 ascii 的时候,
# 在2.x版本,貌似你只能这样, 注意前面是用 u 来让他变为 unicode
# def __repr__(self)
#    return u'<A {}'.format(self.non-ascii-data).encode('utf-8)

# 输出的时候呢,要显示调用 repr()

# print repr(d).decode('utf-8)

if __name__ == '__main__':
    # print sys.argv

    d = D(sys.argv[1], sys.argv[2])
    print type(str(d))
    print d
