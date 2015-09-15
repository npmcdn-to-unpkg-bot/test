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