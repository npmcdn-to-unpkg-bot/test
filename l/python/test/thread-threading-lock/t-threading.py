#!/usr/bin/python
#coding:utf-8

import threading
from time import ctime,sleep


def music(arg):
    for i in range(5):
        print "[%s]: I was listening to %s" %(ctime(), arg)
        sleep(1)

def move(arg):
    for i in range(10):
        print "[%s]: I was at the %s" %(ctime(), arg)
        sleep(1)

threads = []
t1 = threading.Thread(target=music,args=(u'爱情买卖',))
threads.append(t1)
t2 = threading.Thread(target=move,args=(u'阿凡达',))
threads.append(t2)

if __name__ == '__main__':
    for t in threads:
        t.setDaemon(True)
        t.start()

    for t in threads:
        t.join()

    print "[%s]: all over" %ctime()