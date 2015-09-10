#!/usr/bin/python
#coding:utf-8

import logging
logger = logging.getLogger("simple_example")
logger.setLevel(logging.DEBUG)
# create file handler whistreamhandler logs even debug messages
filehandler = logging.FileHandler("spam.log")
filehandler.setLevel(logging.DEBUG)
# create console handler with a higher log level
streamhandler = logging.StreamHandler()
streamhandler.setLevel(logging.ERROR)
# create formatter and add it to the handlers
formatter = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")
streamhandler.setFormatter(formatter)
filehandler.setFormatter(formatter)
# add the handlers to logger
logger.addHandler(streamhandler)
logger.addHandler(filehandler)

# "application" code
logger.debug("debug message")
logger.info("info message")
logger.warn("warn message")
logger.error("error message")
logger.critical("critical message")
