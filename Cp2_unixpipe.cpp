#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <numeric>


int main()
{
	srand(time(NULL)); //for random number generator
	pid_t pid;
	int fd[2];
	int nums[20];
	std::vector<int> vectOne; //for calculating inner product
	std::vector<int> vectTwo; //for calculating inner product
	int innerProduct;
	
	if (pipe(fd) == -1)
	{
		std::cout << "Pipe failed\n";
		exit(EXIT_FAILURE);
	}
	
	pid = fork();
	if (pid < 0)
	{
		std::cout << "Fork failed\n";
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		close(fd[0]); //closes read end of pipe
		std::cout << "child sent into the unnamed pipe:\n";
		for (int i = 0; i < 20; i++) //generates random nums and prints them out
		{
			nums[i] = 49 - (rand() % 99); //assigns value from -49 to 49 inclusive
			std::cout << nums[i];
			if (i == 9 || i == 19) //checks when to add new line
			{
				std::cout << std::endl;
			}
			else //else, put comma
			{
				std::cout << ",";			
			}
		}
		write(fd[1], nums, sizeof(nums) + 1); //sends nums to pipe
		close(fd[1]); //closes write end of pipe
	}
	else
	{
		close(fd[1]); //closes write end of pipe
		read(fd[0], nums, sizeof(nums) + 1); //receives nums from pipe
		std::cout << "parent received from the unnamed pipe:\n";
		for (int i = 0; i < 20; i++) //prints out nums
		{
			std::cout << nums[i];
			if (i == 9 || i == 19)
			{
				std::cout << std::endl;
			}
			else
			{
				std::cout << ",";			
			}
			if (i < 10) //initializing first vector with first ten values of nums
			{
				vectOne.push_back(nums[i]);
			}
			else //initializing second vector with last ten values of nums
			{
				vectTwo.push_back(nums[i]);
			}
		}
		innerProduct = std::inner_product(vectOne.begin(), vectOne.end(), vectTwo.begin(), 0); //calculates inner product
		std::cout << "The inner product between these two vectors is " << innerProduct << std::endl;
	}
	return 0;
}
