# A container which runs nginx, uwsgi and flask.

#FROM ubuntu:14.04
FROM gensmusic/ubuntu-nginx-uwsgi-celery-flask:latest

maintainer gensmusic


# docker 默认是有个entrypoint的 /bin/sh -c的,
# 如果CMD 是 ["echo", "A"]
# 那么默认是执行 /bin/sh -c echo A
# 但是如果你指定了 entrypoint,
# entrypoint entrypoint.sh
# 那么执行就是 entrypoint.sh echo A
# 如果想看到 /bin/sh -c
# 把 CMD [ "echo", "A", "B", "C"] 改成错的
#    CMD [ "echo",  A", "B", "C"]

COPY entrypoint.sh /usr/bin/

ENTRYPOINT ["entrypoint.sh"]
CMD [ "echo", "A", "B", "C"]