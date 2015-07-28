#!/usr/bin/python

import sys
import argparse

# see
# http://blog.chinaunix.net/xmlrpc.php?r=blog/article&uid=21633169&id=4387657

parser = argparse.ArgumentParser()
# args = "*" [0, ...] args
# args = '+' [1, ...) args
parser.add_argument("first", help="first arg", nargs="?", default="99")
parser.add_argument("second", help="second", nargs="?", default="88")


parser.add_argument("-v", "--verbose", help="increase output verbosity", action="store_true")
parser.add_argument("-c", "--choice", help="give me your choice", choices=[0,2,4])
parser.add_argument("-f", "--filename", help="default action=store, type=string")
parser.add_argument("-l", "--list", help="test action acount, try -llll to see list value",
                    default = 0, action="count")

args = parser.parse_args()

def print_args():
    if args.first:
        print 'Fisrt is ',args.first
    if args.second:
        print 'Second is ', args.second


for args_list in [ '', '1', '1 2 3 4 5 6']:
    print 'args:', args_list
    args = parser.parse_args(args_list.split())
    print_args()


# print "-----------\n{}".format(args)