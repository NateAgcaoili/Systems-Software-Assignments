#!/bin/bash


for((j=2; j<=$1; j++)) #loops from 2 to input
	do
		i=2
		flag=0
		while test $i -le `expr $j / 2` #checks if current num j is a prime
			do
				if test `expr $j % $i` -eq 0
				then
					flag=1
				fi

			i=`expr $i + 1`
		done 
	if test $flag -eq 1
	then
		echo "$j is not prime"
	else
		echo "$j is prime" #once printed, starts new iteration with j++
	fi
done

