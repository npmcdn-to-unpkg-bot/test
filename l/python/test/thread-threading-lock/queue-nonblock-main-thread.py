#!/usr/bin/python
#coding:utf-8

import threading
import Queue
import time

q = Queue.Queue(maxsize=10)
boss_thread = None
worker_threads = []

WORKER_TIMEOUT = 5
WORKER_NUMBERS = 2

def worker():
    thread_name = threading.currentThread().getName()
    while True:
        try:
            print '{} is waiting for a task ...'.format(thread_name)
            task = q.get(block=True, timeout=WORKER_TIMEOUT)
            print '{} got a task. doing task...'.format(thread_name)
            time.sleep(1)
            print '{} finished his task ..'.format(thread_name)
            q.task_done()
        except:
            print '{} wait {} seconds and no job, {} is gone...'.format(thread_name, WORKER_TIMEOUT, thread_name)
            break

def boss():
    while True:
        print 'Boss is waiting all task finised...'
        q.join()
        print 'All tasks are done, boss is gone ...'
        break

def start_worker():
    global worker_threads
    if len(worker_threads) == 0:
        for i in range(WORKER_NUMBERS):
            t = threading.Thread(target=worker, name='worker {}'.format(i))
            t.daemon = True
            t.start()
            worker_threads.append(t)
    else:
        for i in range(WORKER_NUMBERS):
            t = worker_threads[i]
            if t is None or not t.is_alive():
                t = threading.Thread(target=worker, name='worker {}'.format(i))
                t.daemon = True
                t.start()
                worker_threads[i] = t

def start_boss():
    global boss_thread
    if boss_thread is None or not boss_thread.is_alive():
        boss_thread = threading.Thread(target=boss, name='boss')
        boss_thread.daemon = True
        boss_thread.start()

def give_task(num):
    for i in range(num):
        print 'put one itme'
        q.put(i)

def check_boss_worker():
    global boss_thread
    global worker_threads
    def check_thread(t):
        if t is None:
            return
        name = t.name
        if t.is_alive():
            print '{} is alive'.format(name)
        else:
            print '{} is not alive'.format(name)

    if boss_thread is None:
        print 'boss is none'
    else:
        check_thread(boss_thread)

    if len(worker_threads) == 0:
        print 'workers are none'
    else:
        for t in worker_threads:
            if t is None:
                print 'worker is gone'
            else:
                check_thread(t)



# first call workers
start_worker()
give_task(10)
start_boss()
check_boss_worker()

time.sleep(7)
give_task(5)
start_boss()

print 'They are working now ...'

time.sleep(15)
check_boss_worker()

