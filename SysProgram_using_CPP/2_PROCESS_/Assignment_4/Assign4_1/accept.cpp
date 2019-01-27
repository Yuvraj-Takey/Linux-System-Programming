#include "header.h"

int main(int argc, char* argv[])
{
	int status;
	if(fork() == 0)
	{
		//Child
		cout<<"Child Thread PID : "<<getpid()<<endl;
		cout<<"Creating Child Process.."<<endl;

		// Converting Child Thread to Self executing Process
		execl("./Child","NULL",NULL);
	}
	else
	{
		//parent
		cout<<"Parent Processs PID : "<<getpid()<<endl;
		
		// wait till child finish his own execution
		wait(&status);
		
		// Here wait completes, mean child completed his execution
		cout<<"*****Exiting Parent*****"<<endl;
	}

	return STATUS_SUC;
}
