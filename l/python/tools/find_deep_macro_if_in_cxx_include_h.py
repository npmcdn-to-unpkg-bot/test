#!/usr/bin/python


import argparse
import os
import shutil
import subprocess
import sys
from multiprocessing import cpu_count

parser = argparse.ArgumentParser()
parser.add_argument("file", help="a .h file")
parser.add_argument("content", help="your connect in the file")

args = parser.parse_args()


f = open(args.file, "r")


a_fake_stack = []

linenum = 0
for line in f:
    linenum += 1
    if line.startswith("#if"):
        a_fake_stack.append(linenum)
    elif line.startswith("#endif"):
        del a_fake_stack[-1]
    elif args.content in line:
        print "Found...."
        break

for k in a_fake_stack:
    print "linenum: {}".format(k)

