FROM ubuntu:16.04

RUN apt-get -qq update >> /dev/null/ &&\
        apt-get upgrade >> /dev/null/ && apt-get -qq install -y g++ libboost-all-dev cmake cmake-data >> /dev/null/

WORKDIR /tmp/recast
COPY src src
COPY headers headers
COPY CMakeLists.txt ./

RUN mkdir build && cd build && cmake .. && make