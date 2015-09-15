#!/usr/bin/python
#coding:utf-8

import logging

_logger = logging.getLogger(__name__)

def log():
    _logger.error('app/main/module:' + __name__)

