

# Proxychains

Debian/Ubuntu:
    $ apt-get install proxychains
Mac OS X:
    $ brew install proxychains-ng

配置文件
编辑      
  mac:    $ vi /usr/local/etc/proxychains.conf
  ubuntu: $ sudo vi /etc/proxychains.conf


[ProxyList]
socks5  127.0.0.1 1080   # use socks5, it will proxy more than http



通过proxychains运行命令：
    $ proxychains curl https://www.twitter.com/
    $ proxychains git push origin master
Or
    $ proxychains bash
    $ curl git push origin master