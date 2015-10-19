#coding:utf-8

from flask import Flask,request, render_template

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/shange')
def shange():
    return render_template('shange.html')

@app.route('/less')
def less():
    return render_template('less.html')

@app.route('/layout')
def layout():
    return render_template('layout.html')

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)
