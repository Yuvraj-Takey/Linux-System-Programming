#include "header.h"

class Accept
{
private:
	int iFD_In;
	char my_File[MAXNAME];
public:	
	struct stat fileStat;
	Accept(const char*);
	~Accept();
	void split();
};

Accept::Accept(const char* file_Name)
{
	strcpy(my_File,file_Name);
	iFD_In = 0;
	
	// create new file for output
	if((iFD_In = open(my_File, O_RDONLY)) == INVALID_FD)
	{
		cout<<"[SORRY]: Unable to open give file"<<endl<<"Reason: "<<strerror(errno)<<endl;
	}
	else
	{
		cout<<"[DONE]: file is successfully opened"<<endl;
	}	
}

void Accept::split()
{
	if(iFD_In == INVALID_FD)
	{
		return;
	}

	FILEINFO stInfo;
	int iRet_Val = 0, iFD_Out = 0;
	char *bufpt = NULL;
	char cPath_Name[MAXNAME] = {'\0'}, cBuffer[MAXBUFF] = {'\0'};

	

	// make new directory in CWD
	iFD_Out = mkdir("Splited",DIR_PERM);
	if(iFD_Out == STATUS_FAILURE)
	{
		cout<<"[SORRY]: Unable to create separate directory\nReason "<<strerror(errno)<<endl;
	}
	else
	{
		// close the directory, as we no need for any operation
		close(iFD_Out);
	}

	
	// traverse till input file not complete
	while((iRet_Val = read(iFD_In,&stInfo,sizeof(stInfo))) > 0)
	{

		// make path to accessible
		strcpy(cPath_Name,"Splited/");
		strcat(cPath_Name,stInfo.cName);

		// create new file with name and permission, which is provided by input file
		if((iFD_Out = open(cPath_Name,O_RDWR|O_CREAT,stInfo.sPermission)) == INVALID_FD)
		{
			cout<<"[SORRY]: Unable to create file in working directory\nReason: "<<strerror(errno)<<endl;
			break;
		}
		
		// allocate dynamic memory for reading data_buffer from input file 
		bufpt = new char[stInfo.iFileLength];
		if(bufpt == NULL)
		{
			cout<<"[SORRY]: problem in dynamic memory creation"<<endl<<"Reason :"<<strerror(errno)<<endl;
		}
		else
		{
			// read data from from input buffer
			if((iRet_Val = read(iFD_In,bufpt,stInfo.iFileLength)) < 0)
			{
				cout<<"[SORRY]: Unable to complete reading operation from given file"<<endl<<"Reason :"<<strerror(errno)<<endl;
			}
			else
			{
				// write data into newly created file
				if((iRet_Val = write(iFD_Out,bufpt,iRet_Val)) < 0)
				{
					cout<<"[SORRY]: Unable to complete reading operation from given file"<<endl<<"Reason :"<<strerror(errno)<<endl;
				}
				else
				{
					// display status of execution
					cout<<"[DONE]:	>\t"<<stInfo.cName<<endl;				
				}
			}
		}

		memset(cPath_Name,0,MAXNAME);				// flush the memory
		memset(&stInfo,0,sizeof(stInfo));			// flush the memory
		delete []bufpt;								// flush the memory
		close(iFD_Out);								// close the file
	}	

	cout<<"[DONE]: Execution finished"<<endl;
}

Accept::~Accept()
{
	if(iFD_In != INVALID_FD)
	{
		close(iFD_In);					// close the file
	}
}

int main(int argc, char* argv[])
{	
	if(argc != ARG_LIMIT)
	{
		cout<<"[ERROR]: Incorrect parameters,\nyour argument count is not matched"<<endl;
		cout<<"[Usage]: <executable_name> <file_name>"<<endl;
		return STATUS_FAILURE;
	}
	
	Accept obj(argv[1]);
	obj.split();	
	
	return STATUS_SUCCESS;
}
