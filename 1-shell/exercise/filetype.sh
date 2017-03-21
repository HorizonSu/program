#!/bin/bash 

FILENAME=$1
BOLD=`tput bold`
SMSO=`tput smso`
SGR0=`tput sgr0`

#echo "input your file:"
#read FILENAME

if [ $# -ne 1 ]
then
	echo error number of arguments;exit
fi

if ! [ -e $FILENAME ]
then 
	echo "$FILENAME is not exists"
	exit
fi

if [ -L $FILENAME ]
then 
	FILETYPE=link
else
	if [ -b $FILENAME ]
	then 
		FILETYPE=block
	else
		if [ -c $FILENAME ]
		then 
			FILETYPE=character
		else
			if [ -d $FILENAME ]
			then 
				FILETYPE=directory
			else
				if [ -f $FILENAME ]
				then
					FILETYPE=regular
				else
					FILETYPE=unkown
				fi
			fi
		fi
	fi
fi

echo "$BOLD $FILENAME $SGR0 is $SMSO $FILETYPE $SGR0 file"
