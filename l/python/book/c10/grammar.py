#!/usr/bin/python
#coding:utf-8


grammar_file = 'grammar.data'
f = open(grammar_file, 'r')

lines = f.readlines()

# get max length for every column
max_lens = [0, 0, 0]
split_lines = [ line.split("@") for line in lines if '@' in line]
for c in range(0,3):
	column = [row[c] for row in split_lines]
	max_lens[c] = max([len(x) for x in column])

# print @ not in
for line in lines:
	if '@' not in line:
		print line.decode('utf-8'),

# print else
max_lens = [x + 1 for x in max_lens]
for row in split_lines:
	for c in range(0, 2):
		left_space = max_lens[c] - len(row[c])
		s = row[c].decode('utf-8') + (' ' * left_space)
		print s,
	# print column 3
	c3 = row[2].split('$')
	for x in range(0, len(c3)):
		if x == 0:
			print c3[x]
		else:
			s = c3[x].replace('%', "  ")
			s = ' ' * (max_lens[0] + max_lens[1]) + s
			print s
exit(1)

for line in f:
	# 把 utf8解码为 unicode然后打印就没有乱码了
	if '@' in line:
		l = line.decode('utf-8').split('@')
		# print (x for x in l)
		print '%s\t\t%s\t\t%s' % (l[0], l[1], l[2])
		# print '{}\t\t{}\t\t{}'.format(l[0], l[1], l[2])
	else:
		print line.decode('utf-8'),
