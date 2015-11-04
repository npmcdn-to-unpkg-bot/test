#!/usr/bin/python
#coding:utf-8

import os
from flask import Flask, session, redirect, url_for, escape, request
from werkzeug import secure_filename

"""
mkdir uploads
"""

UPLOAD_FOLDER="./uploads"
ALLOWED_EXTENSIONS = set(['txt', 'pdf', 'png', 'jpg', 'jpeg', 'gif', '.gz'])

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER


def allowed_file(filename):
    return '.' in filename and \
            filename.rsplit('.', 1)[1] in ALLOWED_EXTENSIONS

@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        file = request.files['file']
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
            return redirect(url_for('upload_file', filename=filename))
    return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form action="" method=post enctype=multipart/form-data>
      <p><input type=file name=file>
         <input type=submit value=Upload>
    </form>
    '''

if __name__ == '__main__':
    # set the secret key.  keep this really secret:
    app.secret_key = 'A0Zr98j/3yX R~XHH!jmN]LWX/,?RT'
    app.run(host='0.0.0.0', debug=True)