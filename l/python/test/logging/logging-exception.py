#!/usr/bin/python
#coding:utf-8

import logging
try:
    1/0
except Exception, e:
    logging.exception(e)

logging.error('logging.exception will print the backtrace for you')
logging.error('logging.exception will NOT stop the program')