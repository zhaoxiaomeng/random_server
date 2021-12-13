#!/bin/bash

mkdir -p '/root/data/currentbak/'
rm -f /root/data/currentbak/*.bin

if [ $# -lt 3 ]; then
	echo "rand.sh 服务端IP 服务端端口 厂商名";
	exit 1;
fi

for (( i=1; i<=1000; i=i+1 ))
do
	echo "++++++++++ round $i ++++++++++"

	/root/random client $1 $2 128k /root/data/currentbak/`printf "%04d" "$i"`.bin
done
chmod a+r /root/data/currentbak/*.bin
mkdir -p /root/data/$3
mv -f /root/data/currentbak/*.bin /root/data/$3/

