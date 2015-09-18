#coding:utf-8
from flask import Flask
from flask_restful import Resource, Api
from flask import Flask,request
from flask.ext.httpauth import HTTPDigestAuth

"""
how to add decorator for every method

因为 Resouce 类是继承自 Flask 的 MethodView，
它能够通过定义 decorators 变量并且把装饰器赋予给它:

你必须定义了才行,
例如,你没有 def get(self).
那么, decorator 是无效的

#

http://www.pythondoc.com/flask-restful/second.html#id4

"""



app = Flask(__name__)
app.config['SECRET_KEY'] = 'hard to guess string'
auth = HTTPDigestAuth()
api = Api(app)

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

class BaseApi(Resource):
    decorators = [auth.login_required]

class HelloWorld(BaseApi):
    def post(self):
        return {'hello' : 'world'}

api.add_resource(HelloWorld, '/')

if __name__ == '__main__':
    app.run(debug=True)