#!/usr/bin/python
#coding:utf-8

from .module import log as module_log
import logging

_logger = logging.getLogger(__name__)

def log():
    _logger.error('app/main/__init__:' + __name__)
    module_log()