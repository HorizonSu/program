#!/bin/bash 

OUTPUTFILE=int.txt
COUNT=1
if [ $# -eq 1 ] && [ -e $1 ]
then
	FILENAME=$1
else
	echo "file is not exists !"
	echo "input your ip manually:"
	FILENAME=""
fi
if [ -e $OUTPUTFILE ]
then 
	rm $OUTPUTFILE
fi

cat $FILENAME | while read IP
do
	a=`echo $IP | cut -d '.' -f1`
	b=`echo $IP | cut -d '.' -f2`
	c=`echo $IP | cut -d '.' -f3`
	d=`echo $IP | cut -d '.' -f4`

	int=`expr $a \* 256 \* 256 \* 256 \
		+ $b \* 256 \* 256 \
		+ $c \* 256 \
		+ $d`
	echo "[$COUNT]-------------------->">>$OUTPUTFILE
	echo "ip:		$IP" >> $OUTPUTFILE
	echo "int:	$int" >> $OUTPUTFILE
	echo "">>$OUTPUTFILE
	COUNT=`expr $COUNT + 1`
done
echo "DONE !!"
echo "the output file is :$PWD/$OUTPUTFILE"
