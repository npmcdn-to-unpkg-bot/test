# install docker
    https://docs.docker.com/engine/installation/linux/ubuntulinux/

    $ sudo apt-get update
    $ sudo apt-get install apt-transport-https ca-certificates
    $ sudo apt-key adv --keyserver hkp://p80.pool.sks-keyservers.net:80 --recv-keys 58118E89F3A912897C070ADBF76221572C52609D
    $ sudo vi /etc/apt/sources.list.d/docker.list
      add the following, for 15.10
      deb https://apt.dockerproject.org/repo ubuntu-wily main

      if you are using others.
        12.04
        deb https://apt.dockerproject.org/repo ubuntu-precise main
        14.04 (LTS)
        deb https://apt.dockerproject.org/repo ubuntu-trusty main
        15.10
        deb https://apt.dockerproject.org/repo ubuntu-wily main
        16.04 (LTS)
        deb https://apt.dockerproject.org/repo ubuntu-xenial main

    $ sudo apt-get update
    $ sudo apt-get purge lxc-docker
    $ apt-cache policy docker-engine

    $ sudo apt-get update
    $ sudo apt-get install linux-image-extra-$(uname -r)

    **now real install**
    $ sudo apt-get udpate
    $ sudo apt-get install docker-engine

    start docker daemon
    $ sudo service docker start

    check to run hello-world
    $ sudo docker run hello-world

# install docker-compose
    // https://docs.docker.com/compose/install/
    // first install docker, then
    $ curl -L https://github.com/docker/compose/releases/download/1.7.0/docker-compose-`uname -s`-`uname -m` > docker-compose
    $ sudo mv docker-compose /usr/local/bin/
    $ sudo chmod +x /usr/local/bin/docker-compose

    $ docker-compose --version

# docker-hub