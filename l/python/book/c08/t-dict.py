#!/usr/bin/python
#coding:utf-8

# 无序,可变

print {} # 空
print {'spam':2, 'egg':3}
print {'food':  {'ham':1, 'egg':2}} # nested
D = dict.fromkeys(['a', 'b'])
print D
D = dict(zip(['key1', 'key2'], ['v1', 'v2', 'v3']))
print D
D = dict(name='bob', age=43)
print D
print D['name'] # key
print 'name' in D # 成员关系 key
print D.keys() # keys
print D.values() # values
print D.items()  # key+ value
print D.copy()   # copy
print D.get('none-key', 'if-no-then-this')
D2 = {'dafei' :12}
D.update(D2)  # 合并
print D
print D.pop('dafei')  #删除
print D
print len(D)
D['name'] = 'dddd'
print D
del D['name']
print D
print list(D.keys())

print { x :x*2 for x in range(10)} #字典解析

# 排序字典
D = {'a':1, 'b':2, 'c':3}
keys = D.keys()
keys.sort()
for k in keys:
	print k,'=>',D[k]