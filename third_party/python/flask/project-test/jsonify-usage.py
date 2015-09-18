#!/usr/bin/python
#coding:utf-8

from flask import Flask, session, redirect, url_for, escape, request, jsonify

app = Flask(__name__)



@app.route('/')
def narmal_usage():
    return jsonify( title='Key-Value usage', name='dafei', attr={'age':10, 'tall':True})

@app.route('/nested')
def nested():
    return jsonify({'title':'with a map' , 'name': 'dafei', 'attr' : {'age':10, 'tall':True}})

@app.route('/<int:return_code>')
def return_code(return_code):
    return jsonify(your_http_return_code=return_code), return_code

@app.route('/test')
def testaa():
    return jsonify(title='test'), 400, {'Location':'aaa'}

if __name__ == '__main__':
    # set the secret key.  keep this really secret:
    app.secret_key = 'A0Zr98j/3yX R~XHH!jmN]LWX/,?RT'
    app.run(debug=True)