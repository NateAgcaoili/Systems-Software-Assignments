#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

class Number{
	protected:
	int num;
	public:
	Number();
	Number(const int n);
	void Cube(){
		int cube;
		cube = num*num*num;
		cout<<"Cube of "<<num<<": "<<cube<<"\n",num;
	}
	void Prime(){
		bool prime = true;
		if (num == 0 || num == 1){
			prime = false;
		}
		else{
			for (int i = 2; i <= num/2; i++){
				if (num % i == 0){
					prime = false;
					break;
				}
			}
		}
		if (prime){
			printf("%d is a prime number.\n",num);
		}
		else{
			printf("%d is not a prime number.\n",num);
		}
	}
};

Number::Number(){
	num = 3232;
}

Number::Number(int n){
	num = n;
}
	
int main()
{
	Number numOne;
	Number numTwo(0);
	Number numThree(3);
	Number numFour(5);
	Number numFive(500);
	numOne.Cube();
	numOne.Prime();
	numTwo.Cube();
	numTwo.Prime();
	numThree.Cube();
	numThree.Prime();
	numFour.Cube();
	numFour.Prime();
	numFive.Cube();
	numFive.Prime();
}
	
	
