#!/usr/bin/python
#coding:utf-8

import json


"""
 重要原则,要不都是 utf-8 + asscii
要不都是 unicode,不能 unicode + utf-8

ensure_ascii=True 会把一个unicode变成字符,
例, 大的 unicode编码是 \u5927
如果 ensure_ascii=True(默认). { 'a' : '大'}
那么, 结果是一个字符串 '{ 'a' : '\u5927'}'
内存值是 \'{"a" : "\\\u5927"}\'
就是完全变成字节流了

"""

ascii_obj = { 
'v1' : 'v2',
'v3' : 'v4'
}
# ensure_ascii=False
result = json.dumps(ascii_obj)
print '-' * 50
print result
print type(result) # str type



# utf-8
utf8_obj = {
    'v1' : '大飞',
    'v2' : '大飞'
}
result = json.dumps(utf8_obj)
print '-' * 50
# If ensure_ascii is True (the default), all non-ASCII characters in the output are escaped with \uXXXX sequences
print result       # {"v1": "\u5927\u98de", "v2": "\u5927\u98de"}
print repr(result) # '{"v1": "\\u5927\\u98de", "v2": "\\u5927\\u98de"}'   变成字节了
print type(result) # str type

result = json.dumps(utf8_obj, ensure_ascii=False)
print '-' * 50
print result       # {"v1": "大飞", "v2": "大飞"}
print repr(result) # '{"v1": "\xe5\xa4\xa7\xe9\xa3\x9e", "v2": "\xe5\xa4\xa7\xe9\xa3\x9e"}'
print type(result) # str type


# unicode obj
unicode_obj = {
    u'v1' : u'大飞',
    u'v2' : u'大飞'
}
result = json.dumps(unicode_obj)
print '-' * 50
print result       # {"v1": "\u5927\u98de", "v2": "\u5927\u98de"}
print repr(result) # '{"v1": "\\u5927\\u98de", "v2": "\\u5927\\u98de"}'  !!!!! 注意和下面的区别 
print type(result) # str type json dumps result default will encode with utf-8 

result = json.dumps(unicode_obj, ensure_ascii=False)
print '-' * 50
print result       # {"v1": "大飞", "v2": "大飞"}
print repr(result) # u'{"v1": "\u5927\u98de", "v2": "\u5927\u98de"}'
print type(result) # type unicode

print result.encode('utf-8')        # {"v1": "大飞", "v2": "大飞"}
print repr(result.encode('utf-8'))  # '{"v1": "\xe5\xa4\xa7\xe9\xa3\x9e", "v2": "\xe5\xa4\xa7\xe9\xa3\x9e"}'

# ascii and unicode obj will be treated as unicode
ascii_unicode_obj = {
    'v1' : u'大飞',
    'v2' : u'大飞'
}
result = json.dumps(ascii_unicode_obj)
print '-' * 50
print result       # {"v1": "\u5927\u98de", "v2": "\u5927\u98de"}
print repr(result) # '{"v1": "\\u5927\\u98de", "v2": "\\u5927\\u98de"}'  !!!!! 注意和下面的区别 
print type(result) # str type json dumps result default will encode with utf-8 

result = json.dumps(ascii_unicode_obj, ensure_ascii=False)
print '-' * 50
print result       # {"v1": "大飞", "v2": "大飞"}
print repr(result) # u'{"v1": "\u5927\u98de", "v2": "\u5927\u98de"}'
print type(result) # type unicode

print result.encode('utf-8')        # {"v1": "大飞", "v2": "大飞"}
print repr(result.encode('utf-8'))  # '{"v1": "\xe5\xa4\xa7\xe9\xa3\x9e", "v2": "\xe5\xa4\xa7\xe9\xa3\x9e"}'

# json loads default make an obj with unicode
obj = json.loads('{"v1": "\xe5\xa4\xa7\xe9\xa3\x9e", "v2": "\xe5\xa4\xa7\xe9\xa3\x9e"}')
print obj

obj = json.loads(u'{"v1": "\u5927\u98de", "v2": "\u5927\u98de"}')
print obj
