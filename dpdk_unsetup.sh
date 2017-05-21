#!/bin/sh
set -e
cd

cd $POFSW_ROOT/~/dpdk-2.2.0

sudo umount -t hugetlbfs nodev /mnt/huge

sudo rm -r x86_64-native-linuxapp-gcc

./tools/dpdk_nic_bind.py --status

echo "Input the number of unbind DPDK ports (even): (Enter)"
read n
echo "Input the str (for example 05:00.0): (Enter and Next One)"
for((i=0;i<n;i++));do
    read port[$i]
done
for((i=0;i<n;i++));do
    sudo ./tools/dpdk_nic_bind.py --bind=igb ${port[$i]}
done

./tools/dpdk_nic_bind.py --status

echo "DPDK Environment Success"

cd
