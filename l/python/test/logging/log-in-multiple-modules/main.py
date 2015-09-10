#!/usr/bin/python
#coding:utf-8

"""
可以看到, 我们在主模块里面定义了一个logger 'spam_application', 并对他进行了配置.

那么在这个解释器进程里面的任何地方去通过getLogger('spam_application')得到的对象都是一样的, 
不需要从新定义配置, 可以直接使用.

更方便的是, 你定义任意该logger的子logger, 都可以共享父logger的定义和配置

所谓的父子logger只是简单的通过命名来识别, 任意以'spam_application.'
开头的logger都是他的子logger, 例如'spam_application.auxiliary'

这个在实际的开发中, 还是很方便的, 对于一个application,

首先通过logging配置文件编写好这个application所对应的log策略, 可以只生成一个根logger, 比如叫'Project'

然后在Main函数里面, 通过fileConfig加载logging的配置

接着在appliction的任意地方, 不同的模块中, 可以使用Project的子logger, 如Project.UI, Project.Core,
 来进行log, 并且不需要反复的定义和配置各个logger.
"""

import logging
import auxiliary_module
# create logger with "spam_application"
logger = logging.getLogger("spam_application")
logger.setLevel(logging.DEBUG)
# create file handler which logs even debug messages
fh = logging.FileHandler("spam.log")
fh.setLevel(logging.DEBUG)
# create console handler with a higher log level
ch = logging.StreamHandler()
ch.setLevel(logging.ERROR)
# create formatter and add it to the handlers
formatter = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")
fh.setFormatter(formatter)
ch.setFormatter(formatter)
# add the handlers to the logger
logger.addHandler(fh)
logger.addHandler(ch)
logger.info("creating an instance of auxiliary_module.Auxiliary")
a = auxiliary_module.Auxiliary()
logger.info("created an instance of auxiliary_module.Auxiliary")
logger.info("calling auxiliary_module.Auxiliary.do_something")
a.do_something()
logger.info("finished auxiliary_module.Auxiliary.do_something")
logger.info("calling auxiliary_module.some_function()")
auxiliary_module.some_function()
logger.info("done with auxiliary_module.some_function()")
