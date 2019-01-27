#include "header.h"
#include <stdio.h>

class Accept
{
private:
	DIR *dir;
	char my_Dir[MAXNAME];
public:	
	Accept(const char*);
	~Accept();
	void Size_Limit();
};

Accept::Accept(const char* dir_Name)	// parameterised
{
	strcpy(my_Dir,dir_Name);

	dir = opendir(my_Dir);
	if(dir == NULL)
	{
		cout<<"[SORRY]: Unable to open directory\nReason: "<<strerror(errno)<<endl;
	}
	else
	{
		cout<<"[DONE]: Directory is successfully opened"<<endl;
	}
}

void Accept::Size_Limit()
{
	if(dir == NULL)
	{
		return;
	}

	struct dirent* Dir_Read;
	struct stat fstat;
	char cFile_Path[MAXNAME] = {'\0'};

	cout<<"[HERE]: Searching files.."<<endl;
	while((Dir_Read = readdir(dir)) != NULL)
	{
		strcpy(cFile_Path,my_Dir);
		strcat(cFile_Path,"/");
		strcat(cFile_Path,Dir_Read->d_name);

		if((stat(cFile_Path,&fstat)) != STATUS_ERR)
		{
			if(S_ISREG(fstat.st_mode))
			{
				if(fstat.st_size > FILE_LIMIT)	// FILE_LIMIT is the macro of 100.
				{
					if((unlink(cFile_Path)) != STATUS_ERR)
					{
						cout<<"[REMOVED]:  "<<Dir_Read->d_name<<endl;
					}
					else
					{
						cout<<"[SORRY]: Unable to unlink the file -"<<Dir_Read->d_name<<endl;
					}
				}
			}
		}

		memset(cFile_Path,0,MAXNAME);
	}

	cout<<"[DONE]: Searching completed"<<endl;
}

Accept::~Accept()
{
	if(dir != NULL)
	{
		closedir(this->dir);
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
	obj.Size_Limit();	
	
	return STATUS_SUC;
}