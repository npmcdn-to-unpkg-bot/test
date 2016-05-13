# OSX install
    $ brew udpate
    $ brew install rabbitmq

# run
PATH=$PATH:/usr/local/sbin to your .bash_profile or .profile. The server can then be started with rabbitmq-server.
    // To have launchd start rabbitmq now and restart at login:
    $ brew services start rabbitmq
    // Or, if you don't want/need a background service you can just run:
    $ rabbitmq-server