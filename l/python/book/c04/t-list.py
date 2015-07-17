#!/usr/bin/python

L = [123, 'spam', 1.23]

print len(L)

print L[0]

print L[:-1]

print L + [4, 5, 6] # make a new list

print L   # we are not changing the original list

# list specific operation

L.append("Ni")
print L # Growing: add object

print L.pop(2)  # Shrinking, delete an item by index

print L

M = ['bb', 'aa', 'cc', 1, 4, 3, 2]
M.sort()
print M

M.reverse()
print M

# Nested
M = [   [1, 2, 3],
        [4, 5, 6],
        [7, 8, 9],
    ]
print M
print M[0]
print M[2][1]

# list comprehension expression
# put every row 1 into a new list 2 in [1,2,3] 5 in [4,5,6] 8 in [7,,8,9]
col2 = [ row[1] for row in M ]
print col2

print [row[1] + 2 for row in M] # add 2 to each item in column 2

print [row[1] for row in M if row[1] % 2 == 0] # Filter out odd items
