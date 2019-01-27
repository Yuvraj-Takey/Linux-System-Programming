#include "header.h"

int main(int argc, char* argv[])
{
	cout<<"[PARENT]: Creating deamon process"<<endl;

	if(fork() == 0)
	{
		if((execl("./deamon","NULL",NULL)) == STATUS_ERR)
		{
			cout<<"[SORRY]: deamon process not created"<<endl;
		}
	}

	cout<<"[PARENT]: Execution completed"<<endl;

	return 0;
}
