#include "header.h"

int main(int argc, char* argv[])
{
	int status;
	if(fork() == 0)
	{
		//Child
		cout<<"[PARENT]: Child Thread PID : "<<getpid()<<endl;
		cout<<"[PARENT]: Creating Child Process.."<<endl;

		// Converting Child Thread to Self executing Process
		execl("./myexe_C1","NULL",NULL);
	}
	else
	{
		//parent
		cout<<"[PARENT]: Processs PID : "<<getpid()<<endl;
		
		// wait till child finish his own execution
		wait(&status);
		
		// Here wait completes, mean child completed his execution
		cout<<"[PARENT]***Exiting***"<<endl;
	}

	return STATUS_SUC;
}
