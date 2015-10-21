#!/usr/bin/python
#coding:utf-8

import requests

#

r = requests.get('http://127.0.0.1:5000',
        json={ 'a' :'b', 'c': '大' },
        headers={'Content-type': 'application/json', 'charset' : 'utf-8' } )

print '-------------reponse headers -----------------------'
print r.headers
print '-------------reponse encoding -----------------------'
print r.encoding # 根据content type 里的 charset 来决定的 ,charset = utf-8
print '-------------reponse content -----------------------'
print r.content         # This is index来设置好
print type(r.content)   # <type 'str'>
print repr(r.content)   # 'This is index\xe6\x9d\xa5\xe8\xae\xbe\xe7\xbd\xae\xe5\xa5\xbd'
print '-------------reponse cookies -----------------------'
print r.cookies


r = requests.get('http://127.0.0.1:5000/charset-not-set', ##### 
        json={ 'a' :'b', 'c': '大' } )

print '-------------reponse headers -----------------------'
print r.headers
print '-------------reponse encoding -----------------------'
print r.encoding # ISO-8859-1
print '-------------reponse content -----------------------'
print r.content         # This is index来设置好
print type(r.content)   # <type 'str'>
print repr(r.content)   # 'This is index\xe6\x9d\xa5\xe8\xae\xbe\xe7\xbd\xae\xe5\xa5\xbd'
print '-------------reponse cookies -----------------------'
print r.cookies



