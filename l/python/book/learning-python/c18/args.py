#!/usr/bin/python
#coding:utf-8

s = """
- 不可变参数"通过拷贝"进行传递
   例如 string和int 你是不能原处改变的
- 可变对象参数的传递是通过引用传递的
   例如字典和列表
- python的参数可以认为是 c++里的 reference传递(既是输入也是输出)
   在函数内部,对可变对象参数的'在原处的修改' 能够影响调用者
"""

print s.decode('utf-8')

def f(a):  # a是通过引用传递进来的
    a = 99 # a指向了另外一个对象,所以并不会改变原来指向的内容
b = 88
f(b)
print b # b is not changed

def changer(a, b):
    a = 2            # 同上,只是改变a的指向而已
    b[0] = 'spame'   # 改变了b的真正内容了
X = 1
L = [1, 2]
print X,L
changer(X, L)
print X,L

s = """
- 避免可变参数的修改
   传入一个 copy 或者在函数内部进行一次 copy
- 传入元组
   # the right way
 """
print s.decode('utf-8')

L = [1, 2]
changer(X, L[:]) # pass a copy
print X,L

def not_changer(a, b):
    b = b[:]
    a = 2
    b[0] = 'spam'
L = [1, 2]
not_changer(X, L)
print X,L

# changer(X, tuple(L)) # 会出错
# print X,L

