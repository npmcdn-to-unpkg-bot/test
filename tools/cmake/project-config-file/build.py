#!/usr/bin/python

import os
import shutil
import subprocess

def run_command(command, verbose = True):
    if verbose:
        print "\n___ running \'{}\'' in \'{}\'\n".format(command, os.getcwd())
    return subprocess.call(command, shell=True)

def exit_if_failed(return_code = 1, msg = "exit"):
    if return_code != 0:
        print msg
        exit(return_code)

build_dir = os.path.join("build", "FooBar")
install_dir = os.path.abspath("staging")


if os.path.exists(build_dir):
    shutil.rmtree(build_dir)
os.makedirs(build_dir)

if os.path.exists(install_dir):
    shutil.rmtree(install_dir)
os.makedirs(install_dir)

os.chdir(build_dir)

exit_if_failed(run_command("cmake -D CMAKE_INSTALL_PREFIX=" + install_dir + " ../../FooBar "))
exit_if_failed(run_command("cmake --build . --target install"))

# build use
build_dir = os.path.join("build", "use-foobar")
os.chdir(os.path.join("..", ".."))

if os.path.exists(build_dir):
    shutil.rmtree(build_dir)
os.makedirs(build_dir)

os.chdir(build_dir)

exit_if_failed(run_command("cmake -D CMAKE_PREFIX_PATH=" + install_dir + " ../../use-foobar "))
exit_if_failed(run_command("cmake --build . "))

