#!/usr/bin/python

s = 'spam'

# """
ss = """  aaaaaaaaa
    bbb'''bbbbbb""bbbbb'bbb
    ccccc
    """
print "[{}]".format(ss)

# stick mutipile lines into one
ss = "  aaaaaaaaa" \
    "bbb'''bbbbbb""bbbbb'bbb" \
    "ccccc"
print "[{}]".format(ss)

# a better way using ()
ss = ("aaaa\n"
    "bbbbbb"
    "cccccc\n"
    "dddddd")
print "[{}]".format(ss)

# len
print len(s)

# index and slice
print s[0]   # s
print s[-1]  # m
print s[-2]  # a
print s[2:4] # am
print s[1:]  # pam
print s[:3]  # spa

# find
print s.find('pa')
print s.find('am')

# replace
print s.replace('pa', 'XYZ') # didn't change s,return a new object
print s

# split
s = 'aaa,bb,cc,dd'
print s.split(",")

# upper
print s.upper()

# isalpha
print s.isalpha()

# strip
s = "  aaa bbb cc \n"
print "[{}]".format(s.rstrip())
print "[{}]".format(s.lstrip())
print "[{}]".format(s.strip())

# format
print "{} is {} big".format("dafei", "very")
print "{0} is {1} big".format("dafei", "very")
print "%s is %s big " % ("dafei", "very")

# help
print dir(s)
help(s.replace)

