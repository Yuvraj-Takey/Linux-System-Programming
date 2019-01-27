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
		// if file is not open then display error message.
		cout<<"\n[SORRY]: Unable to open the file\nError_Code : "<<errno<<endl<<"Reason: "<<strerror(errno)<<endl;
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
