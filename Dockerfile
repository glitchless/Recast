FROM ubuntu:16.04

RUN apt-get -qq update &&\
        apt-get upgrade && apt-get -qq install -y g++ libboost-all-dev cmake cmake-data libc6

WORKDIR /tmp/recast
RUN rm -rf /tmp/recast/*
COPY libs libs
COPY src src
COPY CMakeLists.txt ./

RUN mkdir build && cd build && cmake .. && make
