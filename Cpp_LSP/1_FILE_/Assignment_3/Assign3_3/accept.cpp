/*-------------------------------------------------------------------------------
	Input    	: directory name
	output 		: new directory
 	Question	: Write a a program which accept directory name from user and create 
	              new directory of that name.

    @author Yuvraj Takey
    @version 1.1 March/18
--------------------------------------------------------------------------------*/

#include "header.h"

int main(int argc, char* argv[])
{
	if(argc != ARGS_LIMIT)
	{
		cout<<"Sorry: Incorrect parameters\nusage: <file_name1> <file_name2>"<<endl;
		return (STATUS_FAILURE);
	}
	
	bool sRet_Val;

	Accept obj(argv[1],argv[2]);
	sRet_Val = obj.CheckEqual();
	
	if(sRet_Val == MATCH)	
	{
		cout<<"[DONE]: contents of that two files are equal."<<endl;
	}
	else
	{		
		cout<<"SORRY: contents of that two files are not equal."<<endl;
	}
	
	return (0);
}

