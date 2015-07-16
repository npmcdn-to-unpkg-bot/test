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

# There is a problem, because subprocess is not block anymore,
# so if we read out, there will be an error.
# and we have no way to know when it's going to be ok to read again
# we have to set timer for read and catch the execption like server.py did.
# receive the data
output = process.stdout
r = 'a'
while r:
    r = output.read()
    if r:
        print "Output:{}".format(r)
