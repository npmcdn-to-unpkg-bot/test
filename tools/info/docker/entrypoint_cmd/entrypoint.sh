#!/usr/bin/env bash
# DO NOT forget above

echo "\$@:$@"
echo "\$1:$1"
echo "\$2:$2"
echo "\$3:$3"
echo "\$4:$4"

echo "run original CMD........"
exec "$@"
