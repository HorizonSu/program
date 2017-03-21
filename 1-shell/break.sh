#!/bin/bash 

for value0 in 1 2 3 4 5 6 7
do

	for value1 in 1 2 3 4 5 6 7
	do 
		for value2 in 1 2 3 4 5 6 7 
		do
			if [ $value2 -gt 3 ]
			then 
				break 3
			fi
			echo $value0 -$value1- $value2
		done
		echo "-------------------------------"
	done
	echo "************************************"
done
