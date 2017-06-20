FROM ubuntu:latest

RUN apt-get -qq update && apt-get -qq upgrade && apt-get -qqy install g++ libboost-all-dev cmake cmake-data libc6 libc6-dev sqlite3

WORKDIR /tmp/recast
RUN rm -rf /tmp/recast/*
COPY . .

RUN mkdir build && cd build && cmake .. && make -j$(nproc)