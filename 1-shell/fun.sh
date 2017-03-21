#!/bin/bash 

add()
{
	local value=`expr $1 + $2`
	echo $value
	return 0
}

#receive funtion`s return value
ret=`add $1 $2`

#receive funtion`s status
stat=$?
echo $ret


