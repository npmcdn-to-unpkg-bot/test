#!/usr/bin/python

T = (1,2,3,4,4,5)
print T
print len(T)

print T + (5, 6)
print T

print T[0]
print T.index(4) # 4 first appears at offset 3
print T.count(4) # 4 appears twice

# tuple can't change
# T[0] =2
# T.append(4)