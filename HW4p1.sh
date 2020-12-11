#! /bin/bash

echo The square values are:
for ((i = 0; i <= $1; i++)); do #starts with zero and goes to input value
	printf "`expr $i \* $i` " #prints out i*i with spaces inbetween each square
done
echo #to add new line

