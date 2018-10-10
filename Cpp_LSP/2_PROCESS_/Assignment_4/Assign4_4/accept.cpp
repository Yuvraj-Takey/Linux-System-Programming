#include "header.h"

int main(int argc, char* argv[])
{
	int iStatus;

	cout<<"[PROCESS_1] Hello, I am Parent Process"<<endl;
	cout<<"[PROCESS_1] Pid : "<<getpid()<<endl;

	if(fork() == 0)
	{
		//Child
		cout<<"[PROCESS_1] Creating Process2.."<<endl;

		// Converting Child Thread to Self executing Process
		execl("./myexe_C2","NULL",NULL);
	}

	if(fork() == 0)
	{
		//Child
		cout<<"[PROCESS_1] Creating Process3.."<<endl;

		// Converting Child Thread to Self executing Process
		execl("./myexe_C3","NULL",NULL);
	}

	// Ignore all Death of child signals
	signal(SIGCHLD,SIG_IGN);

	// wait till all child finish his own execution
	wait(&iStatus);
		
	// Here wait completes, mean child completed his execution
	cout<<"[PROCESS_1] Exiting.."<<endl;
	
	return STATUS_SUC;
}