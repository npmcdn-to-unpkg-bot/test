#!/usr/bin/python
#coding:utf-8

import person
bob = person.Person('Bob Smith')
sue = person.Person('Sue Jones', job='dev', pay=10000)
tom = person.Manager('Tom Jones', 50000)

import shelve
db = shelve.open('persondb')
for obj in (bob, sue, tom):
    db[obj.name] = obj
db.close()

db = shelve.open('persondb')
print len(db)
print list(db.keys())

for key in db:
    print key,'=>',db[key]
