#include "header.h"

int main(int argc, char* argv[])
{
	int iStatus;

	if(fork() == 0)
	{
		//Child
		cout<<"[_PARENT] Creating Process_1.."<<endl;

		// Converting Child Thread to Self executing Process
		execl("./myexe_C1","NULL",NULL);
	}

	if(fork() == 0)
	{
		//Child
		cout<<"[_PARENT] Creating Process_2.."<<endl;

		// Converting Child Thread to Self executing Process
		execl("./myexe_C2","NULL",NULL);
	}

	signal(SIGCHLD,SIG_IGN);
	// wait till all child finish his own execution
	wait(&iStatus);
		
	// Here wait completes, mean child completed his execution
	cout<<"[_PARENT] Exiting.."<<endl;
	
	return STATUS_SUC;
}