#!/usr/bin/python

import argparse
parser = argparse.ArgumentParser()
parser.add_argument("square", help="display a square of a given number", type=int)
parser.add_argument("-v", "--verbose", help="increase output verbosity", action="store_true")
parser.add_argument("-c", "--choice", help="give me your choice", choices=[0,2,4])
parser.add_argument("-f", "--filename", help="default action=store, type=string")
parser.add_argument("-l", "--list", help="test action acount, try -llll to see list value",
                    default = 0, action="count")
args = parser.parse_args()

if args.verbose:
    print "square of {} is {}".format(args.square, args.square**2)
else:
    print args.square**2

print "-----------\n{}".format(args)