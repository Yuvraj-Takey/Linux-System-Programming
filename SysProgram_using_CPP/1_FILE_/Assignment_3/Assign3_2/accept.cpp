#include "header.h"

class Accept
{
private:
	int iDirect;
	char my_Dir[MAXNAME];
public:	
	Accept(const char*);
	~Accept();
};

Accept::Accept(const char* dir_Name)	// parameterised
{
	strcpy(my_Dir,dir_Name);

	iDirect = mkdir(my_Dir,DIR_PERM);
	if(iDirect < INVALID_FD)
	{
		cout<<"[SORRY]: Unable to create directory"<<endl<<"Reason: "<<strerror(errno)<<endl;
	}
	else
	{
		cout<<"[DONE]: Directory is successfully created"<<endl;
	}
}

Accept::~Accept()
{
	if(iDirect > INVALID_FD)
	{
		close(iDirect);
	}
}

int main(int argc, char* argv[])
{	
	if(argc != ARG_LIMIT)
	{
		cout<<"[ERROR]: Incorrect parameters,\nyour argument count is not matched"<<endl;
		cout<<"[Usage]: <executable_name> <dir_name>"<<endl;
		return STATUS_ERR;
	}
	
	Accept obj(argv[1]);	
	
	return STATUS_SUC;
}
