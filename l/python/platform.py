#!/usr/bin/python

import platform
import sys
import os

def this_is_a_test():
    return "----this is a test----"

def p(f):
    print "{}:{}".format(f.__name__, f())

# 1. Use sys
# print "sys.platform:{}".format(sys.platform)
print sys.platform
print 1


# 2. Use platform to get detail of system infomation


platform.platform()
# print "platform.platform:{}".format(platform.version())
# print "platform.platform:{}".format(platform.architecture())
# print "platform.platform:{}".format(platform.machine())
# print "platform.platform:{}".format(platform.node())
# print "platform.platform:{}".format(platform.processor())
# print "platform.platform:{}".format(platform.uname())




# print "platform.platform:{}".format(platform.python_build())
# print "platform.platform:{}".format(platform.python_compiler())
# print "platform.platform:{}".format(platform.python_branch())
# print "platform.platform:{}".format(platform.python_implementation())
# print "platform.platform:{}".format(platform.python_revision())
# print "platform.platform:{}".format(platform.python_version())
# print "platform.platform:{}".format(platform.python_version_tuple())