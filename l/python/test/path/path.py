#!/usr/bin/python

import argparse
import os.path

parser = argparse.ArgumentParser()
parser.add_argument("file", help="input a file")

args = parser.parse_args()

test_file = args.file
print "abspath      :{}".format(os.path.abspath(test_file))
print "basename     :{}".format(os.path.basename(test_file))
print "dirname      :{}".format(os.path.dirname(test_file))
print "commonprefix :{}".format(os.path.commonprefix(test_file))
print "getatime     :{}".format(os.path.abspath(test_file))


