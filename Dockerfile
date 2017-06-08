FROM ubuntu:16.04

RUN apt-get -qq update &&\
        apt-get --qq upgrade && apt-get -qq --force-yes install libaudit-dev e2fslibs-dev libblkid-dev build-essential g++ python-dev autotools-dev libicu-dev libbz2-dev libboost-all-dev doxygen doxygen-doc doxygen-latex doxygen-gui graphviz cmake cmake-data

WORKDIR /tmp/recast
COPY src src
COPY ./scripts/generateDocumentationAndDeploy.sh
COPY CMakeLists.txt ./

RUN mkdir build && cd build && cmake .. && make