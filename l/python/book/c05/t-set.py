#!/usr/bin/python

x = set('abcdef')
y = set('bfffffff')

print x
print y

print 'a' in x
print x - y
print x | y
print x & y
print x ^ y

print y
y.add('aaaa') # insert one itme 'aaaa'
print y

y.update(set(['dafei', 'ccccc'])) # merge 
print y

y.remove('b')
print y

for item in set('abc'): print item*3

print {x for x in 'spam'}

# Use set to remove duplicates
L = [1,2,3,3,3,3,3,4]
print L
L = list(set(L))
print L