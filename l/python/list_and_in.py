#!/usr/bin/python



a_list_with_list = [
	["a", "b"],
	["c", "d"],
	["e", "f"],
]

if ["a", "b"] in a_list_with_list:
	print "list can compare and can be used in IN"
else:
	print "list can NOT compare and can NOT be used in IN"
