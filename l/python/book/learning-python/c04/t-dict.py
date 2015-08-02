#!/usr/bin/python

D = { 'food' : 'Spam', 'quantity' : 4, 'color' : 'pink'}
print D

print D['food']

D['quantity'] += 1
print D

# Create a dict
D = {}
D['name'] = 'Bob'
D['job'] = 'dev'
D['age'] = 40
print D
print D['name']

# Sort Key
D = { 'a':1, 'b':2, 'c':3}
print D

keys = D.keys() # unordered keys list
print keys

keys.sort()
print keys # sorted keys list

for key in keys:
    print key,'=>',D[key]

for key in sorted(D): # built-in sorted function
    print key,'=>',D[key]

# if not exists
if not 'f' in D:
    print 'missing'

# get
value = D.get('x', "a-default-value")
print value

value = D['x'] if 'x' in D else "a-default-value" # same way
print value