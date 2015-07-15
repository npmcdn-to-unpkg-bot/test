#!/usr/bin/python

from subprocess import Popen, PIPE
import fcntl, os
import time

process = Popen(["/home/xren/dev/test/l/python/popen/echo.py"], stdin=PIPE, stdout=PIPE, stderr=PIPE)
flags = fcntl.fcntl(process.stdout, fcntl.F_GETFL)
fcntl.fcntl(process.stdout, fcntl.F_SETFL, flags | os.O_NONBLOCK)

# send data
for i in range(5):
    process.stdin.write("dafei" + "\n")
process.stdin.flush()

time.sleep(1) # give stdout time to prepare

# receive the data
output = process.stdout
r = 'a'
while r:
    r = output.read()
    if r:
        print "Output:{}".format(r)
