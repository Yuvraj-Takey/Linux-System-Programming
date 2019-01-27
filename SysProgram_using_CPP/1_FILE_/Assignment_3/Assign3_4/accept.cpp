#include "header.h"

class Accept
{
private:
	DIR *dir;
	char my_Dir[MAXNAME];
public:	
	struct stat fileStat;
	Accept(const char*);
	~Accept();
	void merge(const char*);
};

Accept::Accept(const char* dir_Name)
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

void Accept::merge(const char* file_Name)
{
	if(dir == NULL)
	{
		return;
	}

	int iFD_Out = 0;
	// create new file for output
	if((iFD_Out = creat(file_Name,FILE_PERM)) == INVALID_FD)
	{
		cout<<"[SORRY]: Unable to create file for output operation"<<endl<<"Reason: "<<strerror(errno)<<endl;
		return ;
	}

	int iFD_In = 0;
	struct dirent* Dir_Read;
	int iRet_Val = 0;
	char c_Buffer[MAXBUFF] = {'\0'}, cPath_Name[MAXNAME] = {'\0'};

	cout<<"Searching.."<<endl;

	// traverse the directory till end
	while((Dir_Read = readdir(dir)) != NULL)
	{
		// make path to accessible		
		strcpy(cPath_Name,my_Dir);
		strcat(cPath_Name,"/");
		strcat(cPath_Name,Dir_Read->d_name);
		
		// get the current file information		
		stat(cPath_Name,&fileStat);

		// check for Regular file
		if(S_ISREG(fileStat.st_mode))
		{	
			// open the existing file
			if((iFD_In = open(cPath_Name,O_RDONLY)) > STATUS_FAILURE)
			{
				// read existing file
				if((iRet_Val = read(iFD_In,c_Buffer,MAXBUFF)) >= STATUS_SUCCESS)
				{
					// write byte into output file
					write(iFD_Out,c_Buffer,iRet_Val);
					cout<<">\t"<<cPath_Name<<endl;
				}

				close(iFD_In);
			}
		}

		memset(cPath_Name,0,MAXNAME);			// flush the memory
		memset(c_Buffer,0,MAXBUFF);				// flush the memory
		memset(&fileStat,0,sizeof(fileStat));	// flush the memory
	}

	close(iFD_Out);						// close output file


	cout<<"[DONE]: Execution finished"<<endl;
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
		return STATUS_FAILURE;
	}
	
	Accept obj(argv[1]);
	obj.merge("output");	
	
	return STATUS_SUCCESS;
}
