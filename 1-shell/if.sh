#!/bin/bash 
#if [ $1 -gt 100 ]
if (($1>100))
then
	if test $1 -gt 1000
	then
		echo "$1 > 1000"
	else
		echo "$1 > 100 && $1 <= 1000"
	fi
else 
	if test $1 -lt 50
	then
		echo "$1 < 50"
	else
		echo "$1 >= 50 && $1 <= 100"
	fi
fi

