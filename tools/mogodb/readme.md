# ubuntu install
    $ sudo apt-get install mongodb

    $ sudo service mongodb start/stop


# manually install

    https://docs.mongodb.org/manual/tutorial/install-mongodb-on-linux/

    $ curl -O https://fastdl.mongodb.org/linux/mongodb-linux-x86_64-3.2.5.tgz
    $ tar -zxvf mongodb-linux-x86_64-3.2.5.tgz
    $ sudo mv mongodb-linux-x86_64-3.2.5/ /usr/local/mongodb

    // You can add path into PATH or create links.
    // export PATH=<mongodb-install-directory>/bin:$PATH
    $ find /usr/local/mongodb/bin/* | sudo xargs -i  ln -sf {} /usr/local/bin/

# Run mongodb

    // mongodb default data directry.
    $ mkdir -p /data/db

