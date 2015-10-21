#coding:utf-8

from flask import Flask,request, make_response

app = Flask(__name__)

@app.route('/')
def index():
    print '-------------request ---------------'
    print request
    print '-------------request form---------------'
    print request.form
    print '-------------request args---------------'
    print request.args
    print '-------------request values---------------'
    print request.values
    print '-------------request cookies---------------'
    print request.cookies
    print '-------------request headers---------------'
    print request.headers
    print '-------------request data---------------'
    print request.data
    print '-------------request files---------------'
    print request.files
    print '-------------request method---------------'
    print request.method
    print '-------------request json---------------'
    print request.json
    print u'json get: {}'.format(request.json.get('c'))
    print type(request.json.get('c'))

    print '-------------request path---------------'
    print request.path
    print '-------------request environ---------------'
    print request.environ

    # default flask will encode data to utf-8.
    r = make_response(u'This is index来设置好')
    print '-------------response headers---------------'
    print r.headers  # default Content-Type: text/html; charset=utf-8
    print '-------------response status---------------'
    print r.status
    print '-------------response status_code---------------'
    print r.status_code
    print '-------------response data---------------'
    print r.data
    print 'type of data : {}'.format(type(r.data)) # str, because flask encode it to utf-8
    print '-------------response mimetype---------------'
    print r.mimetype

    return r

@app.route('/charset-not-set')
def hello_world():
        # default flask will encode data to utf-8.
    r = make_response(u'This is index来设置好')
    print '-------------response headers---------------'
    print r.headers  # default Content-Type: text/html; charset=utf-8
    r.headers['Content-Type'] = 'Content-Type: text/html'
    print r.headers  # default Content-Type: text/html; charset=utf-8
    return r


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
