#include "header.h"

int main()
{
		// This call is used for creating process as a DEAMON process
		setsid();
		
		cout<<"[DEAMON]: do not write any User Interaction code inside DEAMON process"<<endl;

		//
		//	aditional code
		//

		sleep(10);

	return 0;
}

