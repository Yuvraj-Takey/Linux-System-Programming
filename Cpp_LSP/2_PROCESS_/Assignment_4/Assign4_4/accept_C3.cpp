#include "header.h"

int main(int argc, char* argv[])
{
	cout<<"[PROCESS_3] Hello, I am Child Process"<<endl;
	cout<<"[PROCESS_3] Pid : "<<getpid()<<endl;
	
	//
	// Additional code
	//

	cout<<"[PROCESS_3] Exiting.."<<endl;
	return STATUS_SUC;
}
