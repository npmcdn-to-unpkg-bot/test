#!/usr/bin/python

import subprocess

"""
some common functions
"""


def run_command(command, verbose = True):
    if verbose:
        print "\n___ running \'{}\'' in \'{}\'\n".format(command, os.getcwd())
    return subprocess.call(command, shell=True)



if __name__ == '__main__':
    print 'This is a tool lib'
