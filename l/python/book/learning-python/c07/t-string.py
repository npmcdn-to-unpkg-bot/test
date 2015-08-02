#!/usr/bin/python
#coding:utf-8
import sys

# 字符串格式化代码
# s  	字符串或者任意对象
# r  	s,但使用repr而不是str
# c  	字符
# d		十进制整数
# i 	整数
# u     无符号整数
# o 	八进制整数
# x 	十六进制整数
# X 	x,但是大写的
# e 	浮点指数
# E     e,但是大写
# f     浮点十进制
# F     浮点十进制
# g     浮点e 或者 f
# G     浮点E 或者F
# %     常量%
#------------------------
#   %[(name)][flags][width][.precision]typecode
print 'dafei ...%d...%-6d....%06d' %(123,123,123)
x = 1.23456789
print '%e | %f | %g | %E' %(x,x,x,x)
print '%-6.2f |%05.2f | %+06.1f' %(x,x,x)
# 基于字典的格式化
print '%(n)d %(x)s' % {"n":1, "x":"dafei"}
reply = """
Hello %(name)s!
your age is %(age)s"""
values = {'name' : "dafei", "age":40}
print reply % values # 我靠帅啊
# format 形式的
template = '{motto} {0} {ham} {1}'
print template.format("is", "haha", motto="dafei", ham="shuai")
# 还可以更强大
print 'My {1[spam]} runs {0.platform}'.format(sys, {'spam': "laptop"})
print 'My {config[spam]} runs {sys.platform}'.format(sys=sys, config={'spam': "laptop"})
# 添加具体格式化
# page 199(原书标记的页码)


# 常见字符串常量和表达式
s = ''  # 空字符串
print s
s = "spam's" # 双引号和单引号相同
print s
s = 's\np\ta00m' # 转移序列, 单引号和双引号是一样的
print s          #            ^^^^^^^^^^^^^^^^^^^^
s = """xxxxx""" # 三重引号字符串
print s
s = r'\temp\spam' # raw字符串,抑制转义 myfile = open(r'C:\ta.txt')
print s

# s1 + s2    	# 合并
# s * 3      	# 重复
# s[i]  		# 索引
# s[i:j] 		# 切片 从i到j-1 不包含j
# s[i:j:k]      # k是间隔的意思,每隔几个就取一个
print 'abcdefghijklmn'[1:10:3]
print 'abcdef'[::-1]  # 负数是说从右往左了
print  len(s)		# 长度
print "a %s %d parrot" % ("kind",13)	#字符串格式化表达式
print "a {0} parrot".format("kind") #2.6 和3.0的格式化方式
s = "  pa,cc "
print s.find('pa')    	# 查找,返回index
print s.rstrip()   		# 去右边空格
print s.replace('pa', 'XX') #替换
print s.split(",")   #分割
print s.isdigit()    # 内容测试
print s.lower()      # 小写
print s.endswith(" ") # 结束测试
print s.join("#####") # 插入分隔符
print s.encode('latin-1') #编码
for x in s: print x   # 迭代
print 'pa' in s # 成员关系
print [ c*2 for c in s ]
print map(ord, s)
print str(11) 		# to str
print int("11") 	# to int
print float("1.3") 	# to float
print str(2.3333333355555555555) # 友好显示
print repr(2.3333333355555555555) # 尽量原样显示
print ord('s')  # 转换为 AscII对应的数字
print chr(115)  # 上面相反的功能