from celery import Celery, Task
import os

#
app = Celery('tasks', backend='redis://localhost:6379/0', broker='redis://localhost:6379/0')
#                      see?   ~~~~~~~~~~~~~~~~~            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

print 'init, pid:{}'.format(os.getpid())

@app.task
def show():
    print 'pid:{}'.format(os.getpid())

    # see, a lot of workers. and they are in seperate process
# [2015-10-27 17:01:11,921: WARNING/Worker-3] pid:26271
# [2015-10-27 17:01:12,644: WARNING/Worker-8] pid:26276
# [2015-10-27 17:01:13,251: WARNING/Worker-6] pid:26274
# [2015-10-27 17:01:13,835: WARNING/Worker-2] pid:26270
# [2015-10-27 17:01:14,443: WARNING/Worker-5] pid:26273
# [2015-10-27 17:01:15,044: WARNING/Worker-1] pid:26269
# [2015-10-27 17:01:15,676: WARNING/Worker-4] pid:26272
# [2015-10-27 17:01:16,473: WARNING/Worker-7] pid:26275

@app.task
def add(x,y):
    return x+y

# http://docs.celeryproject.org/en/latest/userguide/tasks.html#instantiation
# A task is not instantiated for every request, but is registered in the task registry as a global instance.

# This means that the __init__ constructor will only be called once per process,
# and that the task class is semantically closer to an Actor.

class S:
    def __init__(self):
        print 'S init in {}'.format(os.getpid())

    def show(self, who):
        print 'S: {} running in {}'.format(who, os.getpid())

class CustomTask(Task):
    def __init__(self):
        self.pid = os.getpid()
        self.s1 = None
        self.s2 = S()
        self.num = 0
        print 'CustomTask Init in {}:{}'.format(self.pid, os.getpid())

    def run(self):
        self.num = self.num + 1
        print 'This is the {} times run in {}, {}'.format(self.num, self.pid, os.getpid())

        if self.s1 is None:
            self.s1 = S()
        self.s1.show('s1')
        self.s2.show('s2')
        print 's1 is {}, s2 is {}'.format(self.s1, self.s2)

""" celery 应该是先启动一个进程,然后把task注册了.
然后fork了8个进程.应该是先启动一个进程,然后把task注册了.
然后fork了8个进程
这时候,这8个进程都有父进程的数据.
而且都是一模一样.所以,你可以让要在每个
子进程的数据lazy初始化

celery(16319)─┬─celery(16324)
              ├─celery(16325)
              ├─celery(16326)
              ├─celery(16327)
              ├─celery(16328)
              ├─celery(16329)
              ├─celery(16330)
              └─celery(16331)

"""

@app.task
def addone():
    global a_num
    print 'dafei addone:', a_num
    a_num = a_num + 1
    return a_num