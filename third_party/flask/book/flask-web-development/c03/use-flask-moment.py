# -*- coding: utf-8 -*-
"""
moment.js(http://momentjs. com/),它可以在浏览器中渲染日期和时间

$ pip install flask-moment

除了 moment.js,Flask-Moment 还依赖 jquery.js。要在 HTML 文档的某个地方引入这两个
库,可以直接引入,这样可以选择使用哪个版本,也可使用扩展提供的辅助函数,从内容 
分发网络(Content Delivery Network,CDN)中引入通过测试的版本。Bootstrap已经引入
了 jquery.js,因此只需引入 moment.js 即可

Flask-Moment 实现了 moment.js 中的 format()、fromNow()、fromTime()、
calendar()、valueOf() 和 unix() 方法。
你可查阅文档(http://momentjs.com/docs/#/displaying/)学习
"""
from flask import Flask, render_template
from flask.ext.moment import Moment
from flask.ext.bootstrap import Bootstrap
from datetime import datetime


app = Flask(__name__)
moment = Moment(app)
bootstrap = Bootstrap(app)

@app.route('/')
def index():
	return render_template('use-moment.html', current_time=datetime.utcnow())

if __name__ == '__main__':
	app.run(debug=True)
