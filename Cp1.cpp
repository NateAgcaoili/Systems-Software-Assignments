#include <iostream>
#include <map>
#include <unistd.h>
#include <sys/wait.h>

std::map<char, char> compChars; //intializing map for converting chars

void compUpper(std::string str) //prints out complementary uppercase version using compChars map
{
	for (int i = 0; i < str.size(); i++)
	{
		std::cout << compChars[str[i]];
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		std::cout << "Usage: ./Cp1 <lowercase string>\n"; //specifies usage
		exit(EXIT_FAILURE);
	}
	
	compChars['a'] = 'Z'; //setting map keys and paired values
	compChars['b'] = 'Y';
	compChars['c'] = 'X';
	compChars['d'] = 'W';
	compChars['e'] = 'V';
	compChars['f'] = 'U';
	compChars['g'] = 'T';
	compChars['h'] = 'S';
	compChars['i'] = 'R';
	compChars['j'] = 'Q';
	compChars['k'] = 'P';
	compChars['l'] = 'O';
	compChars['m'] = 'N';
	compChars['n'] = 'M';
	compChars['o'] = 'L';
	compChars['p'] = 'K';
	compChars['q'] = 'J';
	compChars['r'] = 'I';
	compChars['s'] = 'H';
	compChars['t'] = 'G';
	compChars['u'] = 'F';
	compChars['v'] = 'E';
	compChars['w'] = 'D';
	compChars['x'] = 'C';
	compChars['y'] = 'B';
	compChars['z'] = 'A';
	
	pid_t pid;
	pid = fork();
	if (pid < 0) //makes sure fork is valid
	{
		std::cout << "Fork failed\n";
	}
	else if (pid == 0) //child process
	{
		std::cout << "I am the child. Printing the original version:\n" << argv[1] << std::endl;
		return 0;
	}
	else if (pid > 0) //parent process
	{
		wait(NULL);
		std::cout << "I am the parent. Printing the complementary uppercase version:\n";
		compUpper(argv[1]);
	}
	return 0;
}
