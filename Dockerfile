FROM gcc:7.1

RUN apt-get -qq update && apt-get -qq upgrade && apt-get -qqy install cmake libboost-all-dev sqlite3

WORKDIR /tmp/recast
RUN rm -rf /tmp/recast/*
COPY . .

RUN mkdir build && cd build && cmake .. && make -j$(nproc)