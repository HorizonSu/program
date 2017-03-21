#!/bin/bash 

convert_ip()
{
	local a=`echo $1 | cut -d '.' -f1`
	local b=`echo $1 | cut -d '.' -f2`
	local c=`echo $1 | cut -d '.' -f3`
	local d=`echo $1 | cut -d '.' -f4`

	local int=`expr $a \* 256 \* 256 \* 256 \
		+ $b \* 256 \* 256 \
		+ $c \* 256 \
		+ $d`
	echo $int
}

get_ip()
{
	local IP
	read IP
	echo $IP
}
echo `convert_ip \` get_ip\``

