#include "header.h"

int main(int argc, char* argv[])
{
	int iPriority_Proc = 0;

	iPriority_Proc = getpriority(PRIO_PROCESS,getpid());

	cout<<"[HERE] Priority of this process is : "<<iPriority_Proc<<endl<<endl;

	return STATUS_SUC;
}
