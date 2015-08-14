#!/usr/bin/python

import sys
sys.path.append('../dcommon.py')
import dcommon as common


"""
Install boost lib in staging
"""

common.run_command('wget http://jaist.dl.sourceforge.net/project/boost/boost/1.59.0/boost_1_59_0.tar.bz2')
