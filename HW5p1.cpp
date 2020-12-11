#include <iostream> 
#include <pthread.h>

int n; //number of threads
int nums[60]; //array of 60 ints
int threadNum = 0; //thread number
int SUM = 0; //sum of array ints
  
void* sumArray(void* arg) 
{ 
	int curThread = threadNum++; //sets current thread and ups threadNum
	for (int i = curThread * (60 / n); i < (curThread + 1) * (60 / n); i++) //calculates where to start and stop for each thread iteration
	{
		SUM += nums[i]; //adds to SUM
	}
	pthread_exit(NULL);
} 
 
int main(int argc, char* argv[]) 
{ 
	if(argc!=2)
	{
		std::cout << "Usage: ./HW5p1 <int 2-6>\n"; //specifies usage
		exit(EXIT_FAILURE);
	}
	n = atoi(argv[1]); //sets n to command line argument
	for (int i = 0; i < 60; i++) //generates 60 integers from 0-59 and assigns to nums
	{
		nums[i] = i;
	}
	std::cout << "Numbers in the array:\n";
	for (int i = 0; i < 60; i++) //prints contents of nums
	{
		std::cout << nums[i] << " ";
	}
	std::cout << std::endl;
	pthread_t threads[n];
	for (int i = 0; i < n; i++) //creates n threads
	{
		pthread_create(&threads[i], NULL, sumArray, (void*)NULL); 
	} 
        
	for (int i = 0; i < n; i++) //joining each thread
	{
		pthread_join(threads[i], NULL); 
	}
    std::cout << "The sum is: " << SUM << std::endl;
  
    return 0; 
} 
