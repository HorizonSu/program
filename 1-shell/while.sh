#!/bin/sh

#
#i=0
#while [ $i -lt 10 ]
#do
#	echo $i
#	i=`expr $i + 1`
#done

i=0
while ((i < 10))
do
	echo $i
	((i ++))
done

echo $((100 + 100))
if ((100 > 100))
then
	echo ok
else
	echo error
fi
