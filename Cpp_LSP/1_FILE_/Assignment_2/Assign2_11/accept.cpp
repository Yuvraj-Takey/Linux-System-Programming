#include "header.h"

class Accept
{
private:
	DIR *dir;
	char my_Dir[MAXNAME];
public:	
	struct stat fileInfo;
	Accept(const char*);
	~Accept();
	void Clean_Up();
};

Accept::Accept(const char* dir_Name)	// parameterised
{
	strcpy(my_Dir,dir_Name);

	dir = opendir(my_Dir);
	if(dir == NULL)
	{
		cout<<"[SORRY]: Unable to open '"<<my_Dir<<"' directory\nReason: "<<strerror(errno)<<endl;
	}
	else
	{
		cout<<"[DONE]: Directory is successfully opened"<<endl;
	}
}

void Accept::Clean_Up()
{
	if(dir == NULL)
	{
		return;
	}

	short sCount = 0;
	struct dirent* Dir_Read;
	char cPath_Name[255] = {'\0'};
	
	cout<<"Searching.."<<endl;
	while((Dir_Read = readdir(dir)) != NULL)
	{
		sprintf(cPath_Name,"%s/%s",my_Dir,Dir_Read->d_name);
		stat(cPath_Name,&fileInfo);
		
		if(S_ISREG(fileInfo.st_mode))
		{	
			if((int)fileInfo.st_size == EMPTY_FIELD)
			{
				sCount++;
				unlink(cPath_Name);
			}
		}

		memset(&fileInfo,0,sizeof(fileInfo));
	}

	if(sCount == 0)
	{
		cout<<"[DONE]: There is no empty files in '"<<my_Dir<<"' directory"<<endl;
	}
	else
	{
		cout<<"[DONE]: Total "<<sCount<<" empty files are removed from '"<<my_Dir<<"' directory"<<endl;
	}
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
	obj.Clean_Up();	
	
	return STATUS_SUC;
}