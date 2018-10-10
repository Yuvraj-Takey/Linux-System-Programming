#include "header.h"

class Accept
{
private:
	DIR *dir;
	int iFD_Out;
	char my_Dir[MAXNAME];
public:	
	struct stat fileStat;
	Accept(const char*);
	~Accept();
	void merge();
};

Accept::Accept(const char* dir_Name)
{
	strcpy(my_Dir,dir_Name);
	iFD_Out = 0;

	dir = opendir(my_Dir);
	if(dir == NULL)
	{
		cout<<"[SORRY]: Unable to open '"<<my_Dir<<"' directory\nReason: "<<strerror(errno)<<endl;
	}
	else
	{
		cout<<"[DONE]: Directory is successfully opened"<<endl;
		
		// create new file for output
		if((iFD_Out = open("allCombine", O_RDWR | O_CREAT, FILE_PERM)) == INVALID_FD)
		{
			cout<<"[SORRY]: Unable to create file for output operation"<<endl<<"Reason: "<<strerror(errno)<<endl;
		}
		else
		{
			cout<<"[DONE]: Output file is successfully created"<<endl;
		}	
	}
}

void Accept::merge()
{
	if((dir == NULL) || (iFD_Out == INVALID_FD))
	{
		return;
	}

	FILEINFO stInfo;
	int iRet_Val = 0, iFD_IN = 0;
	struct dirent* Dir_Read;
	char cPath_Name[MAXNAME] = {'\0'}, cBuffer[MAXBUFF] = {'\0'};

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
			iFD_IN = open(cPath_Name,O_RDONLY);
			if(iFD_IN != INVALID_FD)
			{

				// fill the stInfo structure with necessary information
				memcpy(stInfo.cName,Dir_Read->d_name,Dir_Read->d_reclen);
				stInfo.iFileLength = fileStat.st_size;
				
				// add file permission into file
				stInfo.sPermission = fileStat.st_mode;

				// write that stInfo structure into "output" file
				if((iRet_Val = write(iFD_Out,&stInfo,sizeof(stInfo))) == STATUS_FAILURE)
				{
					cout<<"[SORRY]: Unable to complete write task for '"<<Dir_Read->d_name<<"' file"<<"Reason: "<<strerror(errno)<<endl;
				}
				else
				{
					while((iRet_Val = read(iFD_IN,cBuffer,MAXBUFF)) > 0)
					{
						if((iRet_Val = write(iFD_Out,cBuffer,iRet_Val)) == STATUS_FAILURE)
						{
							cout<<"[SORRY]: Unable to complete write task for '"<<Dir_Read->d_name<<"' file"<<"Reason: "<<strerror(errno)<<endl;			
						}
					}
				}

				memset(&stInfo,0,sizeof(stInfo));	// flush the memory
			}
			else
			{
				cout<<"[SORRY]: unable to open the file"<<endl<<"Reason: "<<strerror(errno)<<endl;
			}
		}

		memset(cPath_Name,0,MAXNAME);			// flush the memory
		memset(&fileStat,0,sizeof(fileStat));	// flush the memory
	}

	cout<<"[DONE]: Execution finished"<<endl;
}

Accept::~Accept()
{
	if(dir != NULL)
	{
		closedir(this->dir);			// close directory
	}

	if(iFD_Out != INVALID_FD)
	{
		close(iFD_Out);					// close the file
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
	obj.merge();	
	
	return STATUS_SUCCESS;
}
