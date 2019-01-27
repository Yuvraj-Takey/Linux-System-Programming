#include "header.h"

int main(int argc, char* argv[])
{
	int iStatus = 0;

	cout<<"[PROCESS_2] Hello, I am Process_2"<<endl;
	cout<<"[PROCESS_2] Pid : "<<getpid()<<endl;

	if(fork() == 0)
	{
		//Child
		cout<<"[PROCESS_2] Creating Process3.."<<endl;

		// Converting Child Thread to Self executing Process
		execl("./myexe_C3","NULL",NULL);
	}
	else
	{
		//parent
		// wait till child finish his own execution
		wait(&iStatus);
		
		// Here wait completes, mean child completed his execution
		cout<<"[PROCESS_2] Exiting.."<<endl;
	}

	return 0;
}