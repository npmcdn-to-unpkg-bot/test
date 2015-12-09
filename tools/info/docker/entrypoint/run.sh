#!/usr/bin/env bash
# DO NOT forget above

echo "aaaaaaaaaaaa"

echo "redis ip:"$REDIS_PORT_6379_TCP_ADDR

echo "start supervisord ..."
supervisord -n
