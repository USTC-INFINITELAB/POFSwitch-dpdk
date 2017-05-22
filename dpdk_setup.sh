#!/bin/sh

set -e

cd net_interfaces

gcc get_interfaces_index.c -o get_interfaces_index.o
sudo ./get_interfaces_index.o

#if [ $? -ne 0 ]
#then
#exit 0
#fi
echo "Network interfaces index get Success"

cd
cd $DPDK_ROOT
#su
#echo 1024 > /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages
#exit
#hugepages=1024
echo "please enter the following command:"
echo "echo 1024 > /sys/kernel/mm/hugepages/hugepages-2048kB/nr_hugepages"
echo "And then please enter exit to exit root"

sudo su

if [ ! -d /mnt/huge ]
then
sudo mkdir /mnt/huge
fi

sudo mount -t hugetlbfs nodev /mnt/huge

sudo make install T=x86_64-native-linuxapp-gcc -j24

sudo modprobe uio_pci_generic

./tools/dpdk_nic_bind.py --status

echo "Input the number of DPDK ports (even): (Enter)"
read n
echo "Input the eth name (for example eth2): (Enter and Next One)"
for((i=0;i<n;i++));do
    read port[$i]
done
for((i=0;i<n;i++));do
    sudo ifconfig ${port[$i]} down
    sudo ./tools/dpdk_nic_bind.py --bind=uio_pci_generic ${port[$i]}
done

./tools/dpdk_nic_bind.py --status

echo "DPDK Environment Success"
cd
