#!/usr/bin/python
#coding:utf-8

import threading
import time

def timeout():
    thread_name = threading.currentThread().getName()
    print 'hello, i am timeout, run in {}'.format(thread_name)

if __name__ == '__main__':
    t0 = threading.Timer(20, timeout)
    t1 = threading.Timer(25, timeout)
    print 'start timer ...'
    t0.start()
    t1.start()

    thread_name = threading.currentThread().getName()
    for i in range(30):
        print 'wait in {} ...'.format(thread_name)
        time.sleep(1)

    # will fail, because thread can only be started once,
    # create a new one
    t0.start()


"""
# when 2 timers are working
t-timer.py(31598)─┬─{t-timer.py}(31599)
                  └─{t-timer.py}(31600)

# when timer1 expired
t-timer.py(31598)───{t-timer.py}(31600)

# when all timers expired
t-timer.py(31598)

"""