#!/usr/bin/python

import argparse
import os

value = "-L../../python/test/"

def get_abspath(value):
    prefix = '-L';
    if value.startswith(prefix):
        new_value = value[len(prefix):]
        print 'pwd:' + os.getcwd()
        new_value = os.path.join(os.getcwd(), new_value)
        return prefix + os.path.abspath(new_value)
    return value


print get_abspath(value)