#!/usr/bin/python
#coding:utf-8

from flask import Flask

app = Flask(__name__)


if __name__ == '__main__':

    # app.debug is set by app.run(debug=True)
    if not app.debug:
        import logging
        from logging.handlers import SMTPHandler
        mail_handler = SMTPHandler('127.0.0.1',
                                   'server-error@example.com',
                                   ADMINS, 'YourApplication Failed')

        # setLevel
        mail_handler.setLevel(logging.ERROR)

        # app into app.logger
        app.logger.addHandler(mail_handler)

        # other libaries
        from logging import getLogger
        loggers = [app.logger, getLogger('sqlalchemy'),
                   getLogger('otherlibrary')]
        for logger in loggers:
            logger.addHandler(mail_handler)
            logger.addHandler(file_handler)