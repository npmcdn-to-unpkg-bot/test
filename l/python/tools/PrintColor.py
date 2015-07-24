#!/usr/bin/python
#coding:utf-8

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def print_color(text, color):
    print color + text + bcolors.ENDC

print_color('dafei', bcolors.HEADER )
print_color('dafei', bcolors.OKBLUE )
print_color('dafei', bcolors.OKGREEN )
print_color('dafei', bcolors.WARNING )
print_color('dafei', bcolors.FAIL )
print_color('dafei', bcolors.ENDC)
print_color('dafei', bcolors.BOLD)
print_color('dafei', bcolors.UNDERLINE)