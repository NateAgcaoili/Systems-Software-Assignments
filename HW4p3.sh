#! /bin/bash

for ((i = 0; i <= $1; i++)); do #starts with zero and goes to input
	if [[ `expr $i % 2` != 0 ]]; then #checks if when you divide i by 2 the remainder is 0
		echo $i #prints number to output
	fi
done

echo 0 #tells c++ program there are no more odd numbers
