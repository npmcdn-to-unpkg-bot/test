#!/usr/bin/env python

import os
import subprocess

def run_command(command, verbose = True):
    if verbose:
        print "\n___ running \'{}\'' in \'{}\'\n".format(command, os.getcwd())
    return subprocess.call(command, shell=True)

def git_config(name, email):
	commands = []
	commands.append('git config user.name ' + name)
	commands.append('git config user.email ' + email)
	for c in commands:
		run_command(c)

if __name__ == "__main__":
	git_config("gensmusic", "gensmusic@163.com")