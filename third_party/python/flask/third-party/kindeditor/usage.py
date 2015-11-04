#coding:utf-8

import os
from flask import Flask,request, render_template, jsonify, url_for

app = Flask(__name__)

basedir = os.path.abspath(os.path.dirname(__file__))

"""
usage:
    $ cd static
    $ wget https://github.com/kindsoft/kindeditor/releases/download/v4.1.10/kindeditor-4.1.10-zh-CN.zip
    $ unzip kindeditor-4.1.10-zh-CN.zip
    $ mv kindeditor-4.1.10 kindeditor
    $ mkdir uploads
"""

def get_upload_dir():
    return os.path.join(basedir, 'static', 'uploads')

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/upload', methods=['POST'])
def upload():
    """
    http://0.0.0.0:5000/upload?dir=image"
    dir: 上传类型，分别为image、flash、media、file

    # 成功时
        {
            "error" : 0,
            "url" : "http://www.example.com/path/to/file.ext"
        }
    # 失败时
        {
            "error" : 1,
            "message" : "错误信息"
        }
    """
    print 'upload args:{}'.format(request.args)
    filepaths = []
    for filename in request.files:
        file = request.files.get(filename)
        file.save(os.path.join(get_upload_dir(), file.filename))
        filepaths.append('uploads/{}'.format(file.filename))

    return jsonify({ 'error': 0, 'url' : url_for('static', filename=filepaths[0])})
    
if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)
