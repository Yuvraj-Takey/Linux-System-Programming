#include "header.h"

class Accept
{
private:
	int fd;
	char my_File[MAXNAME];
public:
	Accept(const char *,int);
	~Accept();
};

Accept::Accept(const char* file_Name, int mode = O_RDONLY)	// parameterised with default constructor
{
	strcpy(my_File,file_Name);

	fd = open(my_File,mode);
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
		cout<<"[DONE]: File is successfully opened with file descripter : "<<fd<<endl;
	}
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
		cout<<"[Usage]: <executable_name> <file_name>"<<endl;
		return STATUS_ERR;
	}
	
	Accept obj(argv[1]);	
	
	return STATUS_SUC;
}
