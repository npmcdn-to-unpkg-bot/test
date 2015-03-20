#!/bin/bash

STAGING_DIR=/home/xren/dev/tmp/osip/bld-linux/staging
SOURCE_FILE="my_osip_utility.cpp osip.cpp"

LINK_O_FILE=""

# simple build
for file in $SOURCE_FILE
do
    g++ -I/usr/local/include -I$STAGING_DIR/include -c $file -o $file.o
    if [ $? -ne 0 ]; then
        echo "build failed"
        exit -1
    fi
    LINK_O_FILE="$LINK_O_FILE $file.o"
done

# simple link
g++ -L$STAGING_DIR/lib -Wl,--start-group \
    $LINK_O_FILE \
    $STAGING_DIR/lib/libosipparser2.a \
    $STAGING_DIR/lib/libosip2.a \
    -Wl,--end-group \
    -lpthread
