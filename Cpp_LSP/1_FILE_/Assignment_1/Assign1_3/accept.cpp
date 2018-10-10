#include <iostream>
#include <unistd.h>
using namespace std;

#define STATUS_ERR -1
#define STATUS_SUC 0

int main(int argc, char* argv[])
{
	//cout<<"HELLO_WORLD"<<endl;
	write(1,"HELLO_WORLD\n",sizeof("HELLO_WORLD\n"));
	
	return STATUS_SUC;
}
