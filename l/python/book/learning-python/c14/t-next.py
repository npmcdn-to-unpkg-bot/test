#!/usr/bin/python
#coding:utf-8

print r'next(X) == x.__next__()'

f = open('data.txt', 'r')
# print f.__next__() # 
while True:
	try:
		print f.next(),
	except Exception, e:
		print 'Iteracte is done'
		break
	else:
		pass
	finally:
		pass

	