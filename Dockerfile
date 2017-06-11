FROM gcc:7.1

# build tools
RUN apt-get update -qq && \
    apt-get install -qq -y cmake

# libs
RUN echo 'deb http://download.opensuse.org/repositories/home:/poletti_marco/Debian_8.0/ /' > /etc/apt/sources.list.d/libfruit.list && \
    apt-get update -qq && \
    apt-get install -qq --allow-unauthenticated -y libboost-all-dev libfruit fruit-dev

# src
WORKDIR /tmp/recast
COPY . .
RUN cmake . && make -j$(nproc)
