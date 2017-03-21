#!/bin/bash 

echo "input your score:"
read score
if [ $score -lt 0 ] || [ $score -gt 100 ]  
then 
	echo "out of range !"
	exit
fi

int=`expr $score / 10`

case $int in 
	10)
		echo "A"
		;;
	9)
		echo "A"
		;;
	8)
		echo "B"
		;;
	7)
		echo "C"
		;;
	6)
		echo "D"
		;;
	*)
		echo "NO PASS"
		;;
esac

