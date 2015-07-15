#!/usr/bin/python                                                                                                                                                      

from subprocess import Popen, PIPE
import fcntl, os
import time
class Server(object):
  def __init__(self, args, server_env = None):
    if server_env:
      self.process = Popen(args, stdin=PIPE, stdout=PIPE, stderr=PIPE, env=server_env)
    else:
      self.process = Popen(args, stdin=PIPE, stdout=PIPE, stderr=PIPE)
    flags = fcntl.fcntl(self.process.stdout, fcntl.F_GETFL)
    fcntl.fcntl(self.process.stdout, fcntl.F_SETFL, flags | os.O_NONBLOCK)
  def send(self, data, tail = '\n'):
    self.process.stdin.write(data + tail)
    self.process.stdin.flush()
  def recv(self, t=.1, e=1, tr=5, stderr=0):
    time.sleep(t)
    if tr < 1:
        tr = 1 
    x = time.time()+t
    r = ''
    pr = self.process.stdout
    if stderr:
      pr = self.process.stdout
    while time.time() < x or r:
        r = pr.read()
        if r is None:
            if e:
                raise Exception(message)
            else:
                break
        elif r:
            return r.rstrip()
        else:
            time.sleep(max((x-time.time())/tr, 0))
    return r.rstrip()
if __name__ == "__main__":
  ServerArgs = ['/home/xren/dev/test/l/python/popen/echo.py']
  server = Server(ServerArgs)
  test_data = '在云端', '云梯', '摩萨德', 'Alisa', 'iDB', '阿里大数据'
  for x in test_data:
    server.send(x)
    print x, server.recv()