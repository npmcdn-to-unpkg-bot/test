#coding:utf-8

from flask import Flask,request
from flask.ext.httpauth import HTTPDigestAuth

"""
pip install flask-httpauth

https://github.com/miguelgrinberg/Flask-HTTPAuth

# use chrome to open http://127.0.0.1:5000

# this needs cookie to work.
curl -u admin:admin http://127.0.0.1:5000 -v --digest -c ./cookie

"""

app = Flask(__name__)
app.config['SECRET_KEY'] = 'hard to guess string'
auth = HTTPDigestAuth()

users = {
    "admin" : "admin",
    "dafei" : "test"
}

@auth.get_password
def get_pw(username):
    if username in users:
        print 'Found user authorization'
        return users.get(username)
    return None

@app.route('/')
@auth.login_required
def index():
    return 'Your authorization name is:%s' % auth.username()

@app.route('/go')
def go():
    return 'Your are logged :%s' % auth.username()


if __name__ == '__main__':
    app.run(debug=True)
