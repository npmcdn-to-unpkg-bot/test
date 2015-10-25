#!/usr/bin/python
#coding:utf-8

j = '{"action": "print", "method": "onData", "data": {"key1" : 1, "key2":"value2"} }'
import json

class Payload(object):
    def __init__(self, j):
        self.__dict__ = json.loads(j)

p = Payload(j)
print '-' * 30
print dir(p)
print '-' * 30
print p.action
print p.method
print p.data
print type(p.data)
data = dict(p.data)
print 'new data:', data

j2 = '{ "identity" :  "dafei", "alert" : "you have message", "badge":1, "payload": { "k1":"v1", "k2" : "v2"} }'
p2 = Payload(j2)
print dir(p2)
print type(p2.payload)
print p2.payload

print '-' *50

class ParseBase(object):
    """docstring for ParseBase"""
    def __init__(self):
        super(ParseBase, self).__init__()
        self.http_status_code = 0

    def parse(self, j):
        dict_data = json.loads(j)
        for key in self.__dict__:
            print 'key:{}'.format(key)
            if not key.startswith('http'):
                value = dict_data.get(key)
                self.__dict__[key] = value

class Http(ParseBase):
    """docstring for Http"""
    def __init__(self):
        super(Http, self).__init__()
        self.name = None
        self.id = None
    
h = Http()
h.parse('{ "name" : "大飞", "id":1 }')
print dir(h)
print h.http_status_code
print h.name
print h.id

