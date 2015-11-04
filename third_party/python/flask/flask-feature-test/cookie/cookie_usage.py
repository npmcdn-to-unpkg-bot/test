#!/usr/bin/python
#coding:utf-8

from flask import Flask, session, redirect, url_for, escape, request, make_response
import datetime

app = Flask(__name__)

@app.route('/')
def index():
    key = 'perment-cookie'
    cookie = request.cookies.get(key, None)
    if not cookie:
        response = make_response("You don't have the cookie, set one for you,expires in 90 days")
        expire_date = datetime.datetime.now()
        expire_date = expire_date + datetime.timedelta(days=90)

        response.set_cookie(key, 'a 90 days cookie', expires=expire_date)
        return response
    return 'You have the perment cookie'

# for session cookie test
@app.route('/session')
def session():
    key = 'session-cookie'
    cookie = request.cookies.get(key, None)
    if not cookie:
        response = make_response("You don't have the cookie, set one for you,expires when browser close")
        response.set_cookie(key, 'a session-cookie')
        return response
    return 'You have the session cookie'


if __name__ == '__main__':
    # set the secret key.  keep this really secret:
    app.secret_key = 'A0Zr98j/3yX R~XHH!jmN]LWX/,?RT'
    app.run(host='0.0.0.0', debug=True)