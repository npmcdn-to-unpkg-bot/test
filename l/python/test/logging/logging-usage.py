#!/usr/bin/python
#coding:utf-8

"""
features
GetLogger

GetLogger() 
    returns a reference to a logger instance with the specified name
    if it is provided, or root if not. The names are period-separated 
    hierarchical structures. Multiple calls to getLogger() with the same 
    name will return a reference to the same logger object.
    后面会看到这种以'.'分隔的hierarchical structures有什么用.

Formatter
    Formatter对象定义了最终log信息的顺序,结构和内容, 后面会详细解释.

Handler
    这儿用到了StreamHandler和FileHandler, 用于向不同的输出端打log.

SetLevel
    Logging有如下级别: DEBUG，INFO，WARNING，ERROR，CRITICAL

    默认级别是WARNING, logging模块只会输出指定level以上的log

    这样的好处, 就是在项目开发时debug用的log, 在产品release阶段不用一一注释, 只需要调整logger的级别就可以了, 很方便的.


Handler

Logging包含很多handler, 可能用到的有下面几种

1. StreamHandler -instances send error messages to streams (file-like objects).
2. FileHandler -instances send error messages to disk files.
3. RotatingFileHandler -instances send error messages to disk files, with support for maximum log file sizes and log file rotation.
4. TimedRotatingFileHandler -instances send error messages to disk files, rotating the log file at certain timed intervals.
5. SocketHandler -instances send error messages to TCP/IP sockets.
6. DatagramHandler -instances send error messages to UDP sockets.
7. SMTPHandler -instances send error messages to a designated email address.
最常用的也就是StreamHandler和FileHandler

 

Configuration

1. Creating loggers, handlers, and formatters explicitly using Python code that calls the configuration methods listed above.
2. Creating a logging config file and reading it using the fileConfig() function.
3. Creating a dictionary of configuration information and passing it to the dictConfig() function.
第一种配置方法前面的code里面已经有了

第二种配置方法, 我觉得在项目里面是比较实用的, 通过编写配置文件, 在code里面只需要用fileConfig配置一下logging, 显得比较简洁.

"""

import logging
import sys

logger = logging.getLogger("test-log")
formatter = logging.Formatter('%(name)-12s %(asctime)s %(levelname)-8s %(message)s', '%a, %d %b %Y %H:%M:%S',)
file_handler = logging.FileHandler("test.log")
file_handler.setFormatter(formatter)
stream_handler = logging.StreamHandler(sys.stderr)

# add handler to logger, now we can output to file and stderr both
logger.addHandler(file_handler)
logger.addHandler(stream_handler)
#logger.setLevel(logging.ERROR)


logger.error("fuckg !!")
logger.removeHandler(stream_handler) # from now, error won't output to sys.stderr
logger.error("wahahahhahaha")