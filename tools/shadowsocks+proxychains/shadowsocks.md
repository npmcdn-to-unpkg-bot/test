# 服务器搭建 http://www.loyalsoldier.me/fuck-the-gfw-with-my-own-shadowsocks-server/
    $ apt-get install python-pip  
    $ pip install shadowsocks  

    $ vim /etc/sysctl.d/local.conf

# 如果想全局代理，可以安装个 proxifier
    https://www.proxifier.com/

# OSX 命令行客户端
    $ brew install shadowsocks-libev 

    # To have launchd start shadowsocks-libev now and restart at login:
    $ brew services start shadowsocks-libev

    # Or, if you don't want/need a background service you can just run:
    $/usr/local/opt/shadowsocks-libev/bin/ss-local -c /usr/local/etc/shadowsocks-libev.json


# linux client
    $ apt-get install python-pip  
    $ pip install shadowsocks  

    启动并永久运行 Shadowsocks 客户端功能：

nohup sslocal -c /root/ss/sslocal.json -d start &

    停止命令:

    sslocal -c /root/ss/sslocal.json -d stop


# qt客户端 install
	https://github.com/shadowsocks/shadowsocks-qt5/wiki/%E5%AE%89%E8%A3%85%E6%8C%87%E5%8D%97

sudo add-apt-repository ppa:hzwhuang/ss-qt5
sudo apt-get update
sudo apt-get install shadowsocks-qt5

	reboot

# 多客户端
    类似这样的
    ss-server -c config1.json -f pid1
    ss-server -c config2.json -f pid2
    ss-server -c config3.json -f pid3

    这样需要你研究一下自启动
