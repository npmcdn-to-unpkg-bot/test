
# go to http://redis.io/
    to download redis-3.0.5.tar.gz

    # you can read README in redis-3.0.5

    $ tar xvf redis-3.0.5.tar.gz
    $ cd redis-3.0.5
    $ make
    $ make test
    $ sudo make install

    // start sever 
    $ redis-server


    // Or if you want redis as a daemon.
    // There will be security issues for default config.
    $ cd utils
    $ sudo ./install-server.sh

# play
    $ redis-cli
    redis> ping
    PONG
    redis> set foo bar
    OK
    redis> get foo
    "bar"
    redis> incr mycounter
    (integer) 1
    redis> incr mycounter
    (integer) 2
    redis> 

# install with docker
    // First install docker and docker-compose

    $ create a docker-compose.yml file
    $ sudo docker-compose up
