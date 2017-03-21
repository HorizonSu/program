#!/bin/bash 
i=0
while [ $i -lt 200 ]
do
	echo "192.168.1.$i">>ip.txt
	i=`expr $i + 1`
done
