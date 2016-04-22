#!/usr/bin/env bash
# DO NOT forget above

echo "\$@:$@"
echo "\$1:$1"
echo "\$2:$2"
echo "\$3:$3"
echo "\$4:$4"

echo "redis ip:"$REDIS_PORT_6379_TCP_ADDR

echo "start supervisord ..."
# supervisord -n
