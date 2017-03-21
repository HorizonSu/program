#!/bin/bash 

#define date
SCORE=$1

#check data
if [ $# -ne 1 ]
then
	echo "error number of argument !"
	exit
fi

#isdigital
if ! expr $SCORE + 1 &>/dev/null
then
	echo "non-integer argument !"
	exit
fi

#if [ $SCORE -lt 0 -o $SCORE -gt 100 ] 
if [ $SCORE -lt 0 ] || [ $SCORE -gt 100 ]
then
	echo "out of range !"
	exit
fi

#process data
case `expr $SCORE / 10` in
	10)
		GRADE=A
		;;
	9)
		GRADE=A
		;;
	8)
		GRADE=B
		;;
	7)
		GRADE=C
		;;
	6)
		GRADE=D
		;;
	*)
		GRADE=E
esac

#output data
echo your grade is : $GRADE

