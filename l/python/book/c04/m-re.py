#!/usr/bin/python

import re

match = re.match('Hello[ \t]*(.*)world', 'Hello    Python world')
print match.groups(1)

match = re.match('/(.*)/(.*)/(.*)', "/usr/home/lum")
print match.groups()

match = re.match('/(.*)/(.*)/(.*)', "/usr/home/lum/aa")
print match.groups()