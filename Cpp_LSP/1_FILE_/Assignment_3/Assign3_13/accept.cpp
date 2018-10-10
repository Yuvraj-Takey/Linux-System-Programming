#include "header.h"

class Accept
{
private:
	DIR *dir;
	int iFD,iDirect;
	char my_file[MAXNAME];
public:
	Accept(const char *,const char *);
	~Accept();
};

Accept::Accept(const char* dir_Name,const char* file_Name)
{
	strcpy(my_file,dir_Name);


	if((dir = opendir(my_file)) == NULL)
	{
		cout<<"[SORRY]: Unable to open directory. Creating new.."<<endl;
		iDirect = mkdir(my_file,DIR_PERM);
		if(iDirect < INVALID_FD)
		{
			cout<<"[SORRY]: Unable to create directory"<<endl<<"Reason: "<<strerror(errno)<<endl;
		}
		else
		{
			cout<<"[DONE]: Directory is successfully created"<<endl;
		}
	}

	strcat(my_file,"/");
	strcat(my_file,file_Name);

	iFD = creat(my_file,FILE_PERM);
	if(iFD < INVALID_FD)
	{
		cout<<"[SORRY]: Unable to create the file\nReason: "<<strerror(errno)<<endl;
	}
	else
	{
		cout<<"[DONE]: File is successfully created"<<endl;
	}
}

Accept::~Accept()
{
	if(dir != NULL)
	{
		closedir(dir);
	}
	else
	{
		close(iDirect);
	}

	if(iFD > INVALID_FD)
	{
		close(this->iFD);
	}
}

int main(int argc, char* argv[])
{	
	if(argc != ARG_LIMIT)
	{
		cout<<"[ERROR]: Incorrect parameters,\nyour argument count is not matched"<<endl;
		cout<<"[Usage]: <executable_name> <Directory name> <file_name>"<<endl;
		return STATUS_ERR;
	}
	
	Accept obj(argv[1],argv[2]);	
	
	return STATUS_SUC;
}
