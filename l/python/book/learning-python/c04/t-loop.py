#!/usr/bin/python

D = { 'a':1, 'b':2, 'c':3}
print D

# for
for key in sorted(D):
    print key,'=>',D[key]

# while
x = 4
while x > 0:
    print 'spam!' * x
    x -= 1

# map and filter fater than for (twice maybe)
# this is twice faster than for
squares = [x**2 for x in [1,2,3,4,5,]]
print squares

# for
squares = []
for x in [1,2,3,4,5]:
    squares.append(x**2)
print squares
