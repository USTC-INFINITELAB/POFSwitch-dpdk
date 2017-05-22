#!/bin/bash
set -e
sudo make uninstall

sudo make clean

sudo aclocal

sudo autoconf

sudo automake

export DPDK_BUILD=$DPDK_ROOT/x86_64-native-linuxapp-gcc

sudo ./configure --with-dpdk=$DPDK_BUILD LIBS=-ldl

sudo make -j24

sudo make install

sudo make clean

echo "POFSwitch install successfully"
