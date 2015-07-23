#!/usr/bin/python
#coding:utf-8

import pickle
# 使用pickle存储python的原声对象

D = {'a':1, 'b':2}

F = open('datafile.pkl', 'wb')
pickle.dump(D, F)  # pickle any object to file
F.close()

F = open('datafile.pkl', 'rb')
E = pickle.load(F)
print E

F.seek(0)
print F.read()
