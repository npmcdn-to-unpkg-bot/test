from flask import Flask
from flask.ext.sendmail import Mail, Message

app = Flask(__name__)
mail = Mail(app)

@app.route('/')
def index():
	msg = Message("hello", sender="dafei@haha.com", recipients=["gensmusic@163.com"])
	msg.body = "testing"
	msg.html = "<b>testing</b>"

	mail.send(msg)
	return 'ok'

if __name__ == '__main__':
	app.run(debug=True)