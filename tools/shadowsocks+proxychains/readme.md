



# Proxychains

Debian/Ubuntu:
    $ apt-get install proxychains // Not working, erorros occur
    # new version of Proxychains
	$ git clone https://github.com/rofl0r/proxychains-ng.git
	$ cd proxychains-ng
	$ ./configure --prefix=/usr --sysconfdir=/etc
	$ make
	$ sudo make install

Mac OS X:
    $ brew install proxychains-ng

配置文件
编辑      
  mac:    $ vi /usr/local/etc/proxychains.conf
  ubuntu: $ sudo vi /etc/proxychains.conf


[ProxyList]
socks5  127.0.0.1 1080   # use socks5, it will proxy more than http



# Ubuntu
通过proxychains运行命令：
    $ proxychains4 curl https://www.twitter.com/
    $ proxychains4 git push origin master
Or
    $ proxychains4 bash
    $ curl git push origin master