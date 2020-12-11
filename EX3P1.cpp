#include <iostream> 
#include <pthread.h>
#include <cstdlib>
#include <unistd.h>

int numbers[10] = {5,4,1,10,20,25,15,19,12,7};
int threadNum = 0; //thread number
int CURNUM = -2;

  
void* evenOdd(void* arg) 
{ 
	int curThread = threadNum++; //sets current thread and ups threadNum
	int curNum = CURNUM+=2; //sets curNum and increments CURNUM by 2
	for (int i = curThread; i < curThread + 1; i++) //calculates where to start and stop for each thread iteration
	{
		if (numbers[curNum] % 2 == 0) //checkking if curNum is even
		{
			std::cout << numbers[curNum] << " is even, thread: " << curThread << std::endl;
		}
		else
		{
			std::cout << numbers[curNum] << " is odd, thread: " << curThread << std::endl;
		}
		if (numbers[curNum + 1] % 2 == 0)
		{
			std::cout << numbers[curNum + 1] << " is even, thread: " << curThread << std::endl;
		}
		else
		{
			std::cout << numbers[curNum + 1] << " is odd, thread: " << curThread << std::endl;
		}
	}
	pthread_exit(NULL);
}

int main() 
{ 
	pthread_t threads[5];
	for (int i = 0; i < 5; i++) //creates 5 threads
	{
		pthread_create(&threads[i], NULL, evenOdd, (void*)NULL);
		sleep(0.1); //to avoid processes acting too quickly
	} 
        
	for (int i = 0; i < 5; i++) //joining each thread
	{
		pthread_join(threads[i], NULL); 
	}
	return 0; 
} 
