#!/usr/bin/env bash

echo 'Download...'
#Get the version of Boost that you require. This is for 1.55 but feel free to change or manually download yourself
wget -O boost_1_55_0.tar.gz http://sourceforge.net/projects/boost/files/boost/1.55.0/boost_1_55_0.tar.gz/download
tar xzvf boost_1_55_0.tar.gz
cd boost_1_55_0/

echo 'Install...'
#Boost's bootstrap setup
./bootstrap.sh --prefix=/usr/local

echo 'Check CPU'
#Find the maximum number of physical cores:
n=`cat /proc/cpuinfo | grep "cpu cores" | uniq | awk '{print $NF}'`

echo 'Install'
#Install boost in parallel
sudo ./b2 --with=all -j $n install

echo 'All!'
#Assumes you have /usr/local/lib setup already. if not, you can add it to your LD LIBRARY PATH
sudo sh -c 'echo "/usr/local/lib" >> /etc/ld.so.conf.d/local.conf'

#Reset the ldconfig
sudo ldconfig
