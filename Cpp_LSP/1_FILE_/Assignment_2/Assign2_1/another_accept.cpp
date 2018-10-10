/*--------------------------------------------------------------
*
* This file contain another logic of same assignment
* this is for future enhancement purpose
*
------------------------------------------------------------*/


#include "header.h"

class Accept
{
private:
	int fd, file_mode;
	//static int file_mode;						//you can also set the static variable from satic method
	char my_File[MAXNAME];
public:
	Accept(const char *,int);
	static short Mode_Check(char*);
	~Accept();
};

Accept::Accept(const char* file_Name, int mode)	// parameterised 
{
	strcpy(my_File,file_Name);
	file_mode = mode;

	fd = open(my_File,file_mode);
	if(fd < INVALID_FD)
	{
		// if file is not open then display error message and try to create the new file
		cout<<"[SORRY]: Unable to open the file\nReason: "<<strerror(errno)<<endl<<"Creating new file..."<<endl;
		fd = creat(my_File,0777);
		if(fd < INVALID_FD)
		{
			cout<<"[SORRY]: Unable to create the file\nReason: "<<strerror(errno)<<endl;
		}
		else
		{
			cout<<"[DONE]: File is successfully created with file descripter : "<<fd<<endl;
		}
	}
	else
	{
		cout<<"[DONE]: File is successfully opend with file descripter : "<<fd<<mode<<endl;
	}
}

/*-------------------------------------------------------------
    Function			: Mode_Check	
	Purpose				: check, given mode is valid or not
	Parameters passed	: string mode
	Return Parameter 	: mode (integral value)
--------------------------------------------------------------*/
short Accept::Mode_Check(char* ARG_mode)
{
	short mode = 0;

	if(strcmp(ARG_mode,"read") == 0)
	{
		mode = O_RDONLY;
		//file_mode = ARG_mode;				// to avoid return value of this function, you can directly set class member from here
	}
	else if(strcmp(ARG_mode,"write") == 0)
	{
		mode = O_WRONLY;
	}
	else if(strcmp(ARG_mode,"read_write") == 0)
	{
		mode = O_RDWR;
	}
	else if(strcmp(ARG_mode,"create") == 0)
	{
		mode = O_CREAT;
	}
	else if(strcmp(ARG_mode,"truncate") == 0)
	{
		mode = O_WRONLY | O_TRUNC;
	}
	else
	{
		cout<<"[ERROR]: Invalid mode argument\nPlease refer README file"<<endl;
		mode = (STATUS_ERR);
	}

	return mode;
}

Accept::~Accept()
{
	if(fd > INVALID_FD)
	{
		close(this->fd);
	}
}

int main(int argc, char* argv[])
{	
	if(argc != ARG_LIMIT)
	{
		cout<<"[ERROR]: Incorrect parameters,\nyour argument count is not matched"<<endl;
		cout<<"[Usage]: <executable_name> <file_name> <file_mode>"<<endl;
		return STATUS_ERR;
	}

	// for file mode variable
	short mode = 0;
	
	// validation for file mode (static method)
	if((mode = Accept::Mode_Check(argv[2])) == (STATUS_ERR))
	{
		return STATUS_ERR;	
	}

	//object creation
	Accept obj(argv[1],mode);
	
	return STATUS_SUC;
}
