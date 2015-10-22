#!/usr/bin/python
#coding:utf-8

import threading
import Queue
import time

q = Queue.Queue(maxsize=10)

def worker():
    thread_name = threading.currentThread().getName()
    while True:
        print '{}:Try to get one time ...'.format(thread_name)
        item = q.get()
        print '{}:Get the task. doing task...'.format(thread_name)
        time.sleep(1)
        print '{}:task is done..'.format(thread_name)
        q.task_done()

for i in range(5):
    t = threading.Thread(target=worker)
    t.daemon = True
    t.start()

for i in range(100):
    print 'put one itme'
    q.put(i)

print 'put is done...'
q.join()
print 'shut down...'

