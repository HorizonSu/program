#!/bin/bash 


arry=("hello" "world" "china")

for ((i = 0; i < 3; i ++))
do
	echo ${arry[$i]}
done

echo _____________________

echo ${arry[*]}
