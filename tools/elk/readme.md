# documents link

    https://www.elastic.co/guide/index.html

# logstash

    https://www.elastic.co/guide/en/logstash/current/index.html

    # install
    # https://www.elastic.co/guide/en/logstash/current/installing-logstash.html

    # 首先要安装java 7 or later 只是运行 Java 程序，而不是开发，下载 JRE 即可
    # http://www.oracle.com/technetwork/java/javase/downloads/jre8-downloads-2133155.html
    # 默认安装1.7在14.04上
    $ sudo apt-get install default-jre
    $ java -version

    # for apt 国内有可能安装不了，因为http timeout
    $ wget -qO - https://packages.elastic.co/GPG-KEY-elasticsearch | sudo apt-key add -
    OK
    $ echo "deb https://packages.elastic.co/logstash/2.3/debian stable main" | sudo tee -a /etc/apt/sources.list
    $ sudo apt-get update && sudo apt-get install logstash

    # 安装binary
    $ wget https://download.elastic.co/logstash/logstash/logstash-2.3.4.tar.gz
    $ tar zvf logstash-2.3.4.tar.gz -C /usr/local
    $ sudo ln -s /usr/local/logstash-2.3.4/bin/logstash /usr/local/bin/logstash

    # 或者 安装deb,
    $ wget https://download.elastic.co/logstash/logstash/packages/debian/logstash_2.3.4-1_all.deb
    $ sudo dpkg -i ogstash_2.3.4-1_all.deb
    # 安装在了 /opt/logstash
    $ sudo ln -s /opt/logstash/bin/logstash /usr/local/bin/logstash

    