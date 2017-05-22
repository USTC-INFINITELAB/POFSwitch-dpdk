# POFSwitch-dpdk Getting Started Guide

## 1. Overview
POFSwitch-dpdk is developed base on the original POFSwitch which you can find at [www.poforwarding.org]().
It performs much better than the original one. Please download and have a try!

### 1.1 Authors and Contributors

* Wenjian Fang [fwj@mail.ustc.edu.cn]
* Quanying Sun [sqy0410@mail.ustc.edu.cn]
* Yuhan Xue
* Qinkun Bao
* Shengru Lee [shengrulee@gmail.com]

### 1.2 Recommended System Requirement

This guide is based on the following system environment:

* Ubuntu 14.04.5 LTS (GNU/Linux 3.13.0-100-generic x86_64)
* gcc version: gcc-4.9.real (Ubuntu 4.9.4-2ubuntu1~14.04.1) 4.9.4
* CPU：Intel(R) Xeon(R) CPU E5-2620 v2 @ 2.10GHz
* Network Interface Card：Intel 82580 or I350

## 2. Installation

### 2.1 Download source codes
```bash
git clone https://github.com/USTC-INFINITELAB/POFSwitch-dpdk.git
git clone https://github.com/USTC-INFINITELAB/dpdk-2.2.0.git
```

### 2.2 Install DPDK environment

Add two environment variables of your POFSwitch-dpdk and dpdk-2.2.0 source codes locations:

```bash
export POFSW_ROOT=~/POFSwitch-dpdk
export DPDK_ROOT=~/dpdk-2.2.0
```

Install the DPDK environment, run:

```bash
cd $POFSW_ROOT
./dpdk_setup.sh
# configure the DPDK hugepages
root$ echo 1024 > /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages
root$ exit
```
Wait for a few seconds, input the number of NICs and the NICs' name you want to bind according to the hints:

![w600](http://ac-HSNl7zbI.clouddn.com/rGNzsieixisqKoWGtSdT5ioStY1XzotTYiVRgFSO.jpg
)

### 2.3 Install POFSwitch-dpdk

```bash
cd $POFSW_ROOT
./setup.sh
```

## 3. Run

You can start the POFSwitch-dpdk:

```bash
sudo pofswitch -i [CONTROLLER_IPADDR] -D -c [COREMASK] -n [NUM]
```

* `-D`: This command parameter specifies the POFSwitch to use DPDK.
* `-c`: An hexadecimal bit mask of the cores to run on. Note that core numbering can change between platforms and should be determined beforehand. 
* `-n`: Number of memory channels per processor socket.

The details of the POFSwitch command parameters you can find at [https://github.com/USTC-INFINITELAB/POFSwitch/blob/master/README.md](https://github.com/USTC-INFINITELAB/POFSwitch/blob/master/README.md).

For example, start a POFSwitch-dpdk to connect to a POFController at 192.168.109.120 and specify to use 4 cores, run:

```bash
sudo pofswitch -i 192.168.109.120 -D -c f -n 4
```

