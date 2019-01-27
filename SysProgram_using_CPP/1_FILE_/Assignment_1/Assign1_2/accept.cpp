#include <iostream>
using namespace std;

#define STATUS_ERR -1
#define STATUS_SUC 0
#define ARG_LIMIT 2

int main(int argc, char* argv[])
{	
	if(argc != ARG_LIMIT)
	{
		cout<<"[ERROR]: Incorrect parameters,\nyour argument count is not matched"<<endl;
		cout<<"[Usage]: <executable_name> <text>"<<endl;
		return STATUS_ERR;
	}
	
	cout<<"Your Text is : "<<argv[1]<<endl;
	
	return STATUS_SUC;
}
