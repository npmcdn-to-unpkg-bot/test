# Bootstrap is an open source framework of Twitter
# http://getbootstrap.com/
# Bootstrap 官方文档(http://getbootstrap.com/)
# 是很 好的学习资源,有很多可以直接复制粘贴的示例

# pip install flask-bootstrap

from flask import Flask, render_template
from flask.ext.bootstrap import Bootstrap

app = Flask(__name__)

bootstrap = Bootstrap(app)

@app.route('/')
def index():
	return render_template('use-bootstrap.html', name='Dafei')

if __name__ == '__main__':
	app.run(debug=True)