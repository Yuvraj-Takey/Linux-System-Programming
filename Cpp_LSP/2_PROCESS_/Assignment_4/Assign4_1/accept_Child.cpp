#include "header.h"

int main(int argc, char* argv[])
{
	cout<<"Hello, I am Child"<<endl;
	cout<<"Child Process Pid : "<<getpid()<<endl;
	
	//
	// code
	//

	cout<<"-----Exiting Child-----"<<endl;
	return STATUS_SUC;
}
