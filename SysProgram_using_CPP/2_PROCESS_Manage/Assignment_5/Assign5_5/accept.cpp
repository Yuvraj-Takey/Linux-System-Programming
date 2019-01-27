#include "header.h"

int main()
{
	char *env = NULL;
	
	env = getenv("HOME");
	if(env == NULL)
	{
		cout<<"[SORRY]: unable to get environment status\nReason"<<endl;
	}
	else
	{
		cout<<"[DONE]: Home directory of the current process is  :"<<env<<endl;
	}

	env = getenv("USER");
	if(env == NULL)
	{
		cout<<"[SORRY]: unable to get environment status"<<endl;
	}
	else
	{
		cout<<"[DONE]: Login user name of the current process is :"<<env<<endl;
	}

    return 0;
}
