#!/usr/bin/python
#coding:utf-8

L = [1,2,3]

i = iter(L)

print i is L # false

while True:
	try:
		print i.next()
	except Exception, e:
		print 'Iteracte is done'
		break
	else:
		pass
	finally:
		pass

i = iter(L)
# print i.__next__()
print next(i)

print 'iteractor for dict'
d = { "A":1, "b":2}
i = iter(d)
print 'key',next(i)
print 'key',next(i)

for key in d:
	print key, '->', d[key]
