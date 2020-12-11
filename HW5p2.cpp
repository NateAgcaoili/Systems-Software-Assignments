#include <iostream> 
#include <pthread.h>
#include <cstdlib>

int matA[5][5], matB[5][5], addAB[5][5]; //creates matA, matB, and addition matrix for matA and matB
int threadNum = 0; //thread number

  
void* addMat(void* arg) 
{ 
	int curThread = threadNum++; //sets current thread and ups threadNum
	for (int i = curThread; i < curThread + 1; i++) //calculates where to start and stop for each thread iteration
	{
		for (int j = 0; j < 5; j++)
		{
			addAB[i][j] = matA[i][j] + matB[i][j]; //adds content of matA and matB to addition matrix
		}
	}
	pthread_exit(NULL);
}

void printArr(int arr[5][5]) //function for printing matrices
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			std::cout << arr[i][j] << "\t";
		}
		std::cout << std::endl; //adds new line after each row
	}
}
 
int main() 
{ 
	srand(time(NULL)); //allows for randomized number differentation for each run
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++) //fills matrix a and matrix b with random numbers from 1 - 20
		{
			matA[i][j] = 1 + (rand() % 20);
			matB[i][j] = 1 + (rand() % 20);
		}
	}
	std::cout << "Matrix A:\n";
	printArr(matA);
	std::cout << "Matrix B:\n";
	printArr(matB);
	pthread_t threads[5];
	for (int i = 0; i < 5; i++) //creates 5 threads
	{
		pthread_create(&threads[i], NULL, addMat, (void*)NULL); 
	} 
        
	for (int i = 0; i < 5; i++) //joining each thread
	{
		pthread_join(threads[i], NULL); 
	}
  	std::cout << "The sum is:\n";
  	printArr(addAB);
	return 0; 
} 
