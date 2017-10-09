FROM ubuntu:16.04

ENV DEBIAN_FRONTEND noninteractive

ARG UID=1000

RUN useradd -u $UID stepik -m
RUN ["/bin/bash", "-c", "chown $UID /home/stepik"]
RUN ["apt-get", "-qq", "update"]
RUN ["apt-get", "install", "-y", "apt-utils"]
RUN ["apt-get", "install", "-y", "nano"]

USER stepik

ENV EDITOR=nano

VOLUME ["/home/stepik"]

WORKDIR "/home/stepik"

ENTRYPOINT ["nano"]
