#include "header.h"

int main(int argc, char* argv[])
{
	cout<<"[PROCESS_2] Hello, I am Process_2"<<endl;
	cout<<"[PROCESS_2] Pid : "<<getpid()<<endl;
	
	//
	// Additional code
	//

	cout<<"[PROCESS_2] Exiting.."<<endl;
	return STATUS_SUC;
}
