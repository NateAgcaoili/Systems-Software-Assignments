#include <iostream>
#include <unistd.h>

int main()
{
	fork();
	fork();
	std::cout << "Process id: " << getpid() << std::endl;
	return 0;
}
