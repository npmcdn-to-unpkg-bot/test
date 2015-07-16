#!/usr/bin/python

print "a",
print "b",
print "c", # , will not print a newline
print ""

for i in [ "a", "b", "c" ]:
    if i == "c":
        print i
    else:
        print i,