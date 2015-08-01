#!/usr/bin/python
#coding:utf-8

s = """
__init__          构造函数        对象建立
__del__           析构函数        对象收回
__add__           运算符+         如果没有 _iadd_, X+Y, X += Y
__or__            运算符|(位OR)   如果没有_ior_, X|Y, X|=Y
__repr__          打印,转换       print X, repr(X), str(X)
__str__   
__call__          函数调用        X(*args, **kargs)
__getattr__       点号运算        X.undefined
__setattr__       属性赋值        X.any = value
__delattr__       属性删除        del X.any
__getattribute__  属性获取        X.any
__getitem__       索引运算        X[key], X[i:j],没__iter__时的for循环和其他迭代器
__setitem__       索引赋值        X[key] = value, X[i:j] = sequence
__delitem__       索引和分片删除  del X[key], del X[i:j]
__len__           长度            len(X), 如果没有 __boo__,真值测试
__bool__          布尔测试        bool(X), 真测试
__lt__,__gt__     特定比较        X<Y, X>Y
__le__,__ge__                     X<=Y, X>=Y
__eq__,__ne__                     X==Y, X!=Y
__radd__          右侧加法        other + X
__iadd__          实地加法        X += Y(or else __add__)
__iter__,__next__ 迭代环境        i=iter(X), next(I), for loops
__contains__      成员关系测试    item in X
__index__         整数值          hex(X), bin(X), oct(X), O[X], O[X:]
__enter__         环境管理器      with obj as var:
__exit__
__get__           描述符属性      X.attr, X.attr=value, del X.attr
__set__
__delete__        see c37
__new__           创建(see c39)   在__init__之前创建对象
__sub__     
"""

print s.decode('utf-8')

class Indexer:
    def __getitem__(self, index):
        return index ** 2

x = Indexer()
for i in range(5):
    print x[i],
print ''