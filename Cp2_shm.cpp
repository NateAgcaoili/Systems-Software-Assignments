#include <iostream>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <sstream>

std::string genStrNums() //generates random numbers in string form and prints them out
{
	std::string nums = "";
	int num = 0;
	for (int i = 0; i < 20; i++)
	{
		num = 49 - (rand() % 99);
		nums += std::to_string(num);
		std::cout << num;
		if (i == 9 || i == 19)
		{
			std::cout << std::endl;
		}
		else
		{
			std::cout << ",";
		}
		nums+=" ";
	}
	return nums;
}

char* strToCharPointer(std::string str) //converts string to char pointer
{
	char * writable = new char[str.size() + 1];
	std::copy(str.begin(), str.end(), writable);
	writable[str.size()] = '\0';
	return writable;
}

int main()
{
	srand(time(NULL));
	const int SIZE = 4096;
	const char *name = "OS";
	pid_t pid;
	int shm_fd;
	void *ptr;

	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}
	else if (pid > 0) {  //parent process
		wait(NULL);
		shm_fd = shm_open(name, O_RDONLY, 0666); //opens the shared memory segment
		if (shm_fd == -1) {
			std::cout << "open shared memory failed\n";
			exit(-1);
		}
		ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0); //maps the shared memory segment in the address space of the process
		if (ptr == MAP_FAILED)
		{
			std::cout << "Map failed in parent\n";
			exit(-1);
		}
		std::string ptrStr = std::string((char *)ptr); //converts ptr to string
		std::cout << "parent read from the shared memory:\n";
		int number;
		int i = 0;
		int j = 0;
		std::stringstream iss(ptrStr);
		std::vector<int> vectOne;
		std::vector<int> vectTwo;
		while (iss >> number) //converting string to vectors for calculating inner product
		{
			if (i < 10)
			{
				vectOne.push_back(number);
			}
			else
			{
				vectTwo.push_back(number);
			}
			i++;
		}
		i = 0;
		while (i < 20) //printing out received ptr
		{
			if (i < 10)
			{
				if (i == 9)
				{
					std::cout << vectOne[i] << std::endl;
				}
				else
				{
					std::cout << vectOne[i] << ",";
				}
			}
			else
			{
				if (i == 19)
				{
					std::cout << vectTwo[j] << std::endl;
				}
				else
				{
					std::cout << vectTwo[j] << ",";
				}
				j++;
			}
			i++;
		}
		int innerProduct = std::inner_product(vectOne.begin(), vectOne.end(), vectTwo.begin(), 0); //calculates inner product
		std::cout << "The inner product between these two vectors is " << innerProduct << std::endl;
		if (shm_unlink(name) == -1) //removes the shared memory segment
		{
			std::cout << "Error removing " << name << std::endl;
			exit(-1);
		}
	}
	else { 
		std::cout << "child wrote into the shared memory:\n";
		const char *sharedNums= strToCharPointer(genStrNums());
		shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666); //creates shared memory segment
		if (shm_fd == -1)
		{
			std::cout << "open shared memory failed\n";
			exit(-1);
		}
		ftruncate(shm_fd,SIZE); //configures the size of the shared memory segment
		ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0); //maps the shared memory segment in the address space of the process
		if (ptr == MAP_FAILED) {
			std::cout << "Map failed in child\n";
			return -1;
		}
		void *ptr2=ptr;//backs up the pointer for later use
		sprintf((char *)ptr,"%s",sharedNums);//writes ptr to shared memory region
		ptr += strlen(sharedNums);
	}
	return 0;
}

