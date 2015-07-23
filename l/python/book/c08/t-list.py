#!/usr/bin/python
#coding:utf-8

# list 有序, 可变 跟数组似的

# list常用操作
L = [] 			# 空list
L = [0,1,2,3]  # index from 0 to 3
L = ['abc', ['def', 'ghi']]	# nested
L = list('spam')
print L
L = list(range(-4, 4))
print L
# L[i]  		# index
# L[i][j]		
# L[i:j]		# slice
len(L)			# len
# L1 + L2 		# 合并
print L * 3		# 重复
for x in L: print x # 成员关系
print 3 in L
L.append(9)		# 修改
L.extend([5,6,7])
print L
L.insert(1, 88) # index 1 insert 88
print L
print L.index(1) # 返回1所在的index
print L.count(1) # count
L.sort() # 排序,会改变
print L
L.reverse()
print L
del L[0]  # 删除index 0 的元素
print L
del L[0:3] #  删除 [0.3) 的元素
print L
print L.pop()   # 删掉最后一个????
print L
L.remove(3) # 删掉元素是3的
print L
L[0:3] = [] #相当于把 [0,3)给删掉了
print L
L[0] = 99
print L
L[0:3] = [7,8,9,0]
print L

print [x**2 for x in range(5)] # 列表解析
print list(map(ord, 'spam'))
