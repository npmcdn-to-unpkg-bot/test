#!/usr/bin/python
#coding:utf-8

from .main import log as main_log
from .module import log as module_log
import logging


print 'Init logger for ', __name__
_root_logger = logging.getLogger(__name__)
# Add handler for logger or you will see No handlers could be found for logger "app"
ch = logging.StreamHandler()
# set format
formatter = logging.Formatter("[%(asctime)s][%(levelname)s][%(name)s] %(message)s")
ch.setFormatter(formatter)

_root_logger.addHandler(ch)


def log():
    _root_logger.error('app/__init__:'+ __name__)
    module_log()
    main_log()