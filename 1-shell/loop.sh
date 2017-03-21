#!/bin/bash  

#for ((i = 0; i < 100000; ))
i=0
j=0
while [ $j -lt 10 ]
do
	while [ $i -lt 10 ]
	do
		echo "*************"
		if [ $i -eq 5 ]
		then
			break 2;
		fi
		((i ++))
	done
	((j++))
	echo "---------------"
done
echo $i
