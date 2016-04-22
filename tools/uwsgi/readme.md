# uwsgi

# 基本常用命令
# 如果自己是服务器

    $ uwsgi --http :9090 --wsgi-file foobar.py --master --processes 4 --threads 2 --stats 127.0.0.1:9191

# --status 是给 uwsgitop用的
    $ pip install uwsgitop
    $ uwsgitop 127.0.0.1:9191


# 如果在 nginx等服务器后面,且用 socket 127.0.0.1:3031作为通信
    $ uwsgi --socket 127.0.0.1:3031 --wsgi-file foobar.py --master --processes 4 --threads 2 --stats 127.0.0.1:9191

# .ini file see uwsgi.ini
    $ uwsgi yourfile.ini

# for flask
    $ uwsgi --socket 127.0.0.1:3031 --wsgi-file myflaskapp.py --callable app --processes 4 --threads 2 --stats 127.0.0.1:9191
    # myflask.py == manage.py
    # need --callable app

# 关于你程序里自己写的thread
# http://uwsgi-docs.readthedocs.org/en/latest/WSGIquickstart.html#a-note-on-python-threads
    默认你程序里的thread是不会启动的,如果要启动,
    加 --enable-threads
    or in .ini file
    enable-threads = true

# 并发
    --threads 8      [ threads = 8 ] .ini
    --processes 4    [ processes = 4 ] .ini

# 产品最好用这个,来监控子进程
    --master

# 配置 nginx 和 uwsgi
# 这个很好啊
# http://uwsgi-docs.readthedocs.org/en/latest/tutorials/Django_and_nginx.html#configure-nginx-for-your-site
# http://uwsgi-docs.readthedocs.org/en/latest/Nginx.html
