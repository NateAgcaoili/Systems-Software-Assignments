#include <iostream>

class Student
{
	unsigned int studentID;
	public:
        Student(unsigned int studentID)
        {
            this -> studentID = studentID;
        }
		void CheckPalindrome()
		{
			int n = studentID;
			int reverse = 0;
            int lastDigit = 0;
			do //creates a reverse form of studentID
			{
				lastDigit = n % 10;
				reverse = (reverse * 10) + lastDigit;
				n = n/10;
			} while (n!=0);
			if (studentID == reverse) //checks if reverse is same as original
			{
				std::cout << "The number " << studentID << " is a palindrome\n";
			} else
			{
				std::cout << "The number " << studentID << " is not a palindrome\n";
			}
		}
};

int main()
{
	Student nate = Student(901003989);
	nate.CheckPalindrome();
}
