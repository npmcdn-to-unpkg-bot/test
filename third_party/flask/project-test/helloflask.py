#coding:utf-8

from flask import Flask,request

app = Flask(__name__)

@app.route('/')
def index():
    return 'This is index'

@app.route('/hello')
def hello_world():
    return 'hello_world'

# 转换器有下面几种
# int     接受整数
# float   同 int, 但是接受浮点数
# path    和默认的相似, 但也接受斜线
@app.route('/usr/<usrname>')
def show_usr_profile(usrname):
    return 'User %s' % usrname

@app.route('/post/<int:post_id>')
def show_post(post_id):
    return 'Post %d' % post_id

# 唯一 URL / 重定向行为
# Flask 的 URL 规则基于 Werkzeug 的路由模块. 这个模块背后的思想是基于 Apache 以及更早的 HTTP 服务器主张的先例, 保证优雅且唯一的 URL
# 第二种情况的 URL 结尾不带斜线，类似 UNIX-like 系统下的文件的路径名。访问结尾带斜线的 URL 会产生一个 404 “Not Found” 错误
@app.route('/projects/')
def projects():
    return 'The project page'

@app.route('/about')
def about():
    return 'The about page'

# HTTP方法
@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        return 'You are using POST'
    else:
        return 'You are using GET'

@app.route('/test')
def test():
    with app.test_request_context('/login', method='POST'):
        return 'browsing %s with method %s' % (request.path, request.method)

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)
