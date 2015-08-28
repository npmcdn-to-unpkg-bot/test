#!/usr/bin/python
#coding:utf-8

# Python对with的处理还很聪明。基本思想是with所求值的对象必须有一个__enter__()方法，一个__exit__()方法。

class Sample:
    def __enter__(self):
        print 'In Sample::__enter__'
        return 'Foo'
    def __exit__(self, type, value, trace):
        print 'In Sample::__exit__'

def get_sample():
    return Sample()


# exception
class Sample2:
    def __enter__(self):
        return self # return self
    def __exit__(self, type, value, trace):
        print 'type:', type
        print 'value:', value
        print 'trace:', trace
    def do_something(self):
        bar = 1/0
        return bar + 10

def get_sample2():
    return Sample2()



if __name__ == '__main__':
    with get_sample() as s:
        print 'Sample:', s # s is the return value of __enter__

    with get_sample2() as s:
        s.do_something()
