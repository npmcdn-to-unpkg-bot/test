#!/usr/bin/python
#coding:utf-8

from flask import Flask, session, redirect, url_for, escape, request

app = Flask(__name__)

@app.before_request
def before_request():
    print 'This is before request'

@app.route('/')
def index():
    print 'This is index'
    return 'This is index'


if __name__ == '__main__':
    # set the secret key.  keep this really secret:
    app.secret_key = 'A0Zr98j/3yX R~XHH!jmN]LWX/,?RT'
    app.run(debug=True)