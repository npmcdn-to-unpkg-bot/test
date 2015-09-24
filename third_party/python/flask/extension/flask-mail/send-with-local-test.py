import os
from flask import Flask
from flask.ext.mail import Mail, Message
"""
Didn't work
"""
basedir = os.path.abspath(os.path.dirname(__file__))

app = Flask(__name__)
app.config['SECRET_KEY'] = 'hard to guess string'


mail = Mail(app)

@app.route('/', methods=['GET', 'POST'])
def index():
    msg = Message('flask-mail using localhost',
                  sender='flask-mail@haha.com', recipients=['gensmusic@163.com'])
    msg.body = 'This is from flask-mail'
    msg.html = '<b>This is from flask-mail</b>'
    mail.send(msg)
    return 'Hi'


if __name__ == '__main__':
    app.run(debug=True)
