#!/usr/bin/python

import subprocess
import sys

filename = sys.argv[1]

f = open(filename, "w")
f.write("#!/usr/bin/python\n\n")
f.close()

subprocess.call("chmod +x " + filename, shell=True)
