#include <iostream>
#include <stdlib.h>		// for atoi()
using namespace std;

#define STATUS_ERR -1
#define STATUS_SUC 0
#define ARG_LIMIT	3

class Accept
{
private:
	int iSum;
public:
	Accept();
	void Calculate_Sum(int,int);
	void Display();
};

Accept::Accept()
{
	iSum = 0;	// initialize class variable
}

void Accept::Calculate_Sum(int iNo1, int iNo2)
{
	iSum = iNo1 + iNo2;
}

void Accept::Display()
{
	cout<<"Addition of two number is : "<<iSum<<endl;
}

int main(int argc, char* argv[])
{
	if(argc != ARG_LIMIT)
	{
		cout<<"[ERROR]: Incorrect parameters,\nyour argument count is not matched"<<endl;
		cout<<"[Usage]: <executable_name> <number1> <number2>"<<endl;
		return STATUS_ERR;
	}

	if(((atoi(argv[1])) == 0) || ((atoi(argv[2])) == 0))
	{
		cout<<atoi(argv[1])<<atoi(argv[2])<<endl;
		cout<<"[SORRY]: Given input is invalid\nPlease refer README file"<<endl;
		return STATUS_ERR;
	}

	// object creation
	Accept obj;
	obj.Calculate_Sum(atoi(argv[1]),atoi(argv[2]));
	obj.Display();

	return STATUS_SUC;
}
