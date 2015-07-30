#!/usr/bin/python
#coding:utf-8

import os
import shutil

unexists_file = 'unexists_file'
if os.path.exists(unexists_file):
    print unexists_file,' exists with os.path.exists'
else:
    print unexists_file,' doesnt exists with os.path.exists'


dst_path = 'dafeihome'
if os.path.exists(dst_path):
    # link failed on this
    print 'Remove the link'
    shutil.rmtrees(dst_path)

if os.path.islink(dst_path):
    print dst_path,' is a link'
    os.unlink(dst_path)

os.symlink(os.path.abspath('/home/xren') , dst_path)