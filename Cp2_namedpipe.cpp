#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <cstdlib>
#include <vector>
#include <numeric>
 
void child(char *path)
{
	int fd;
	ssize_t num;
	int nums[20];
	
	std::cout << "child sent into the named pipe:\n";
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
	fd = open(path, O_WRONLY);//makes child write only
	if(fd==-1)
	{
		std::cout << "in child, open error = " << errno << ", msg = ";
		strerror(errno);
		exit(-1);
	}

	num = write(fd, nums, sizeof(nums) + 1);//writer will not start to write until reader has opened the named pipe
	close(fd);
}
 
void parent(char *path)
{
	int fd;
	ssize_t num;
	int nums[20];
	std::vector<int> vectOne; //for calculating inner product
	std::vector<int> vectTwo; //for calculating inner product
	int innerProduct;


	fd = open(path, O_RDONLY);//makes parent read only
	if(fd==-1)
	{
		std::cout << "in child, open error = " << errno << ", msg = ";
		strerror(errno);
		exit(-1);
	}
	num=read(fd, nums, sizeof(nums)+1);
	std::cout << "parent received from the named pipe:\n";
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
	close(fd);
	unlink(path);
}

int main()
{

	srand(time(NULL));
	char path[1024];//stores absolute path of named pipe
	if (getcwd(path, sizeof(path)) == NULL)
	{
		perror("getcwd() error");
		exit(0);
	}
	strcat(path,"/fifoCp2");
	pid_t pid;

	setlinebuf(stdout); //setting buffering method for stdout
	unlink(path); //remove link to path
	int r=mkfifo(path, 0600); //making named pipe named path
	if(r==-1)
	{
		std::cout << "in main, mkfifo error = " << errno << ", msg = ";
		strerror(errno);
		exit(-1);
	}
	pid = fork();
	if(pid<0)
	{
		std::cout << "in main, fork call error = " << errno << ", msg = ";
		strerror(errno);
		exit(-1);
	}
	else if (pid == 0)
	{
		child(path);//child process is the writing end
	} else {
		parent(path);//parent process is the reading end
	}
	return 0;
}
