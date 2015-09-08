from celery import Celery
print 'run this how many times??? 11'

app = Celery('tasks', backend='amqp://guest@localhost//', broker='amqp://guest@localhost//')

print 'run this how many times??? 22'
a_num = 0

@app.task
def add(x,y):
    return x+y

@app.task
def addone():
    global a_num
    print 'dafei addone:', a_num
    a_num = a_num + 1
    return a_num