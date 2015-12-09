# A container which runs nginx, uwsgi and flask.

#FROM ubuntu:14.04
FROM gensmusic/ubuntu-nginx-uwsgi-celery-flask:latest

maintainer gensmusic


EXPOSE 80

COPY run.sh /usr/bin/run.sh
ENTRYPOINT ["run.sh"]