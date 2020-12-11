#! /bin/bash

echo The numbers between 0 to 100 that are divisible by both 3 and 5 are:
for ((i = 0; i <= 100; i++)); do #starts with zero and goes to 100
	if [[ `expr $i % 3` == 0 && `expr $i % 5` == 0 ]]; then #checks if i is divisible by both 3 and 5
		printf "$i " #prints i if correct
	fi
done
echo #to add new line

