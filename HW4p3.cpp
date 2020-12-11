#include <iostream>
#include <cmath>

void printCube(int num) //recursively prints cubes of all odd numbers
{	int num2;
	if (num%2!=0) //checks if number is odd
		{
			num = pow(num,3); //cubes number
			std::cout << num << " "; //prints cubed number with space after
			std::cin >> num2; //gets next number
			printCube(num2); //prints next cube
		}
	else
	{
		std::cout << std::endl; //ends when there are no more odd numbers
	}
}

int main(int argc, char *argv[]) //main method
{
	int num;
	std::cin >> num; //gets first number
	printCube(num); //starts recursive loop
	return 0;
}


