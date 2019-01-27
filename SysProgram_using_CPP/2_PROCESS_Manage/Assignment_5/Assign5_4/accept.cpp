#include "header.h"

// The  variable  environ  points  to  an array of pointers to strings called the "environment".
extern char **environ;


// you can use the above global variable as well as the third parameter of main function
// both will work same
int main(int argc, char* argv[], char* envp[])
{
	// get the temporary variable to store the address of global_environ 
	char** Proc_Environment = environ;

	// Traverse till end.
	while(*Proc_Environment != NULL)
	{
   		cout<<*Proc_Environment<<endl;

   		// increment Proc_Environment to get next value
   		Proc_Environment++;
	   	}

    return 0;
}
