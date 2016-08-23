
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

    Or
    $ sudo apt-get install redis-server

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

# command
### var [set, get, incr, del]
    > set name "bob"
    OK
    > get name
    "bbb"
    > set aa 10
    OK
    > incr aa
    (integer) 11
    > del name
    (integer) 1

### 查看所有keys
    > keys *
### 删除所有keys
    > flushdb

### life [expire, ttl]
    > set name "bob"
    > ttl name
    (integer) -1  # never expired
    > expire name 10
    > ttl name   # after one second
    (integer) 9
    > ttl name
    (integer) -2 # expired

### list [rpush, lpush, rpop, lpop, llen, lrange]
    > rpush friends "bob"
    (integer) 1
    > rpush friends "lily"
    (integer) 2
    > lpush friends "susan"
    (integer) 3
    > lrange friends 0 -1
    1) "susan"
    2) "bob"
    3) "lily"
    > llen friends
    (integer) 3
    > lpop friends
    > rpop friends

### set [sadd, srem, sismember, smembers]
    > sadd a_set "a"  # 1 success
    (integer) 1
    > sadd a_set "b"
    (integer) 1
    > sadd a_set "c"
    (integer) 1
    > srem a_set "c" # 1 success 0 failed
    (integer) 1
    > sismember a_set "a"
    (integer) 1
    > sismember a_set "c"
    (integer) 0
    > smembers set
    1) "a"
    2) "c"

### sorted set[zadd, zrange]
    > zadd sorted 0 "a"
    (integer) 1
    > zadd sorted 11 "b"
    (integer) 1
    > zadd sorted 2 "c"
    (integer) 1
    > zrange sorted 0 -1
    1) "a"
    2) "c"
    3) "b"

### hset [hset, hdel, hmset, hgetall, hget]
    > hset user:1000 name "bob"
    (integer) 1
    > hset user:1000 email "bob@bob.com"
    (integer) 1
    > hset user:1000 password "12345"
    (integer) 1
    > hgetall user:1000
    1) "name"
    2) "bob"
    3) "email"
    4) "bob@bob.com"
    5) "password"
    6) "12345"
    > hget user:1000 name
    "bob"
    > hmset user:1001 name "lily" email "lily@lily.com" password "2324"
    OK
    > hset user:1000 visits 10
    (integer) 1
    > hincrby user:1000 visits 2
    (integer) 12
    > hdel user:1000 visits
    (integer) 1
    > hincrby user:1000 visits 33
    (integer) 33
