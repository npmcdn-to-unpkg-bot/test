from flask import Flask
from flask.ext.email import ConsoleMail, EmailMessage, send_mail

app = Flask(__name__)
mailbox = ConsoleMail(app)

@app.route('/')
def index():
    email = EmailMessage('Sub', 'Content', 'dafei@dafei.com',
        ['gensmuisc@163.com'])
    email.send(mailbox)
    return 'ok'

if __name__ == '__main__':
    app.run(debug=True)