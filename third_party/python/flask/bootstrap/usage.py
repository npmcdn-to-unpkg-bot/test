#coding:utf-8

from flask import Flask,request, render_template

app = Flask(__name__)

pages = (
    ('shange', u'预定义栅格类'),
    ('less', u'Less mixin 和变量'),
    ('layout', u'排版'),
    ('html_body_width_height', u'Html body width height test'),
    ('center_element', u'center-element'),
    ('bootstrap_table', u'bootstrap table')
)

@app.route('/')
def index():
    return render_template('index.html', pages=pages)

@app.route('/shange')
def shange():
    return render_template('shange.html')

@app.route('/less')
def less():
    return render_template('less.html')

@app.route('/layout')
def layout():
    return render_template('layout.html')

@app.route('/html_body_width_height')
def html_body_width_height():
    return render_template('html_body_width_height.html')

@app.route('/center-element')
def center_element():
    return render_template('center-element.html')

@app.route('/bootstrap-table')
def bootstrap_table():
    return render_template('bootstrap-table.html')

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)
