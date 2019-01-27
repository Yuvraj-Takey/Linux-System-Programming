#include "header.h"

class Accept
{
private:
	DIR *dir;
	char my_Directory[MAXNAME];
public:
	Accept(const char *);
	void one_KB();
	~Accept();
};

Accept::Accept(const char* file_Name)
{
	memset(my_Directory,0,MAXNAME);
	strcpy(my_Directory,file_Name);

	if((dir = opendir(my_Directory)) != NULL)
	{
		cout<<"[DONE]: Directory is successfully opened"<<endl;
	}
	else
	{
		cout<<"[SORRY]: Unable to open the Directory"<<endl<<"Reason: "<<strerror(errno)<<endl;
	}
}

void Accept::one_KB()
{
	if(dir == NULL)
	{
		return;
	}

	int iRet_Val = 0, iFD = 0;
	struct dirent* dir_read = NULL;
	struct stat fstat;
	char cPath_Name[MAXNAME] = {'\0'};

	while((dir_read = readdir(dir)) != NULL)
	{
		// make relative path
		strcpy(cPath_Name,my_Directory);
		strcat(cPath_Name,"/");
		strcat(cPath_Name,dir_read->d_name);

		// file stat
		stat(cPath_Name,&fstat);

		// check for regular file
		if(S_ISREG(fstat.st_mode))
		{
			// open the file
			if((iFD = open(cPath_Name,O_RDWR)) <= INVALID_FD)		// INVALID_FD is the MACRO of (-1)
			{
				cout<<"[SORRY]: Unable to open "<<cPath_Name<<endl<<"Reason: "<<strerror(errno)<<endl;
			}
			else
			{
				// check for file size
				if(fstat.st_size < FILE_SIZE_LIMIT)		// FILE_SIZE_LIMIT is the MACRO of 1024
				{	
					// seek till end of the file
					if((iRet_Val = lseek(iFD,(HOLE_SIZE-(fstat.st_size)),SEEK_END)) == STATUS_ERR)
					{
						cout<<"[SORRY]: Unable to seek in "<<cPath_Name<<endl;
						continue;   // go for next file
					}

					// write something to ensure, the HOLE IN FILE
					if((iRet_Val = write(iFD,"*",BYTE)) <= INVALID_WRITE)
					{
						cout<<"[SORRY]: Unable to create Hole in "<<cPath_Name<<endl;
					}
					else
					{
						cout<<"[DONE]: _HOLE >\t\t"<<dir_read->d_name<<endl;
					}
				}
				else
				{
					// truncate the file from FILE_SIZE_LIMIT
					if((iRet_Val = ftruncate(iFD,FILE_SIZE_LIMIT)) == STATUS_ERR)
					{
						cout<<"[SORRY]: Unable to truncate "<<cPath_Name<<endl<<"Reason: "<<strerror(errno)<<endl;
					}
					else
					{
						cout<<"[DONE]: TRUNK >\t\t"<<dir_read->d_name<<endl;
					}
				}

				// close the file
				close(iFD);
			}
		}

		// vanish memory
		memset(cPath_Name,0,MAXNAME);			
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
		cout<<"[Usage]: <executable_name> <directory_name>"<<endl;
		return STATUS_ERR;
	}
	
	Accept obj(argv[1]);
	obj.one_KB();	
	
	return STATUS_SUC;
}
