#!/bin/bash 


read X OPT Y
if [ "$OPT" == "*" ]
then
	echo `expr $X \* $Y`
else
	echo `expr $X $OPT $Y`
fi

