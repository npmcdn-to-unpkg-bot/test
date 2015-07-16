#!/usr/bin/python


a_map = {
	["a", "b"] : "v1",
	["c", "d", "e"] : "v2",
}

for k in a_map:
	print k
	print a_map[k]

# we can't use list as key, but we can use list as value