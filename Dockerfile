FROM gcc:7.1

# build tools
RUN apt-get update -qq && \
    apt-get install -qq -y cmake

# libs
RUN apt-get update -qq && \
    apt-get install -qq -y libboost-all-dev

# src
WORKDIR /tmp/recast
COPY . .
RUN cmake . && make -j$(nproc)
