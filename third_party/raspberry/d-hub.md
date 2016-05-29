# 挂着硬盘
    # 使用ntfs的硬盘可以避免权限问题

    $ sudo fdisk -l
    Disk /dev/sda: 931.5 GiB
              ^^^

    $ sudo mkdir -p /d-hub/media
    $ sudo chmod 777 /d-hub/media
    $ sudo unmount /dev/sda
    $ sudo mount /dev/sda /d-hub/media


    # 开机自动挂载
    $ sudo apt-get install fuse-utils ntfs-3g
    $ modprobe fuse
    $ sudo vi /etc/fstab
    /dev/sda /d-hub/media ntfs-3g defaults,noexec,umask=0000 0 0

# dlna
    $ sudo apt-get update
    $ sudo apt-get install minidlna

    # 配置文件, 默认监听ip就行，只需要设置目录和名字就行
    $ sudo vi /etc/minidlna.conf

    # 开机启动
    $ sudo update-rc.d minidlna defaults

    # 常用命令
    $ sudo service minidlna start/stop/force-reload

    # 常看资源, 替换成自己的ip
    http://192.168.1.100:8200

# transmission
    $ sudo apt-get install transmission-daemon

    # 配置，配置之前要先stop，否则配置文件会被覆盖
    $ sudo service transmission-daemon stoop
    sudo vi /etc/transmission-daemon/settings.json
        "download-dir": "/d-hub/media",
       "rpc-enabled": true,
        "rpc-password": "xxxxx", // 填写名字，他会自动加密的
        "rpc-port": 9091,
        "rpc-url": "/download/", // web控制的路径
        "rpc-username": "download", // web登录会用
        "rpc-whitelist": "192.168.1.*",
        "rpc-whitelist-enabled": true,

    # sudo service transmission-daemon start/stop

    # web控制
    http://192.168.1.100:9091/download

# ftp
    $ sudo apt-get install vsftpd
    $ sudo vi /etc/vsftpd.conf

