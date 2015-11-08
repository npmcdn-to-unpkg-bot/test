#coding:utf-8

from flask import Flask,request, render_template

app = Flask(__name__)

pages = (
    ('shange', u'预定义栅格类'),
    ('less', u'Less mixin 和变量'),
    ('layout', u'排版'),
    ('html_body_width_height', u'Html body width height test'),
    ('center_element', u'center_element'),
    ('bootstrap_center_text', u'bootstrap_center_text'),
    ('bootstrap_center_image', u'bootstrap_center_image'),
    ('click_open_a_frame', u'点击弹框'),
    ('click_show_big_picture', u'点击图片查看原图'),
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

@app.route('/center_element')
def center_element():
    return render_template('center_element.html')

@app.route('/bootstrap_center_text')
def bootstrap_center_text():
    return render_template('bootstrap_center_text.html')

@app.route('/bootstrap_center_image')
def bootstrap_center_image():
    return render_template('bootstrap_center_image.html')

@app.route('/click_open_a_frame')
def click_open_a_frame():
    return render_template('click_open_a_frame.html')

@app.route('/click_show_big_picture')
def click_show_big_picture():
    return render_template('click_show_big_picture.html')

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)
