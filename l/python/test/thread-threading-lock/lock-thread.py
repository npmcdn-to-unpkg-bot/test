#!/usr/bin/python
#coding:utf-8

"""
Python多线程thread与threading实现
http://www.pythonclub.org/python-basic/threading

python的thread模块是比较底层的模块，python的threading模块是对thread做了一些包装的，可以更加方便的被使用。

这里需要提一下的是python对线程的支持还不够完善，不能利用多CPU，但是下个版本的python中已经考虑改进这点，让我们拭目以待吧。

threading模块里面主要是对一些线程的操作对象化了，创建了叫Thread的class。

一般来说，使用线程有两种模式，一种是创建线程要执行的函数，把这个函数传递进Thread对象里，让它来执行；另一种是直接从Thread继承，创建一个新的class，把线程执行的代码放到这个新的 class里。

我们来看看这两种做法吧。

"""

import string, threading, time

def thread_func(arg):
    global count, mutex
    # get thread name
    thread_name = threading.currentThread().getName()
    for x in range(0, int(arg)):
        # get the lock
        mutex.acquire()
        count += 1
        # release the lock
        print thread_name, x, count
        mutex.release()

        time.sleep(1)

def main(num):
    global count, mutex
    threads = []

    count = 1
    # create a lock mutex
    mutex = threading.Lock()

    # create thread
    for x in range(0, num):
        threads.append(threading.Thread(target=thread_func, args=(10,)))

    # run all threads
    for t in threads:
        t.start()

    # main thread wait
    for t in threads:
        t.join()

if __name__ == '__main__':
    num = 4
    # create num threads
    main(num)