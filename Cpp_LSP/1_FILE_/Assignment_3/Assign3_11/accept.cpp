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
	void GetMaxFile();
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

void Accept::GetMaxFile()
{
	if(iFD_In == INVALID_FD)
	{
		return;
	}

	FILEINFO stInfo;
	char cCheck;
	int iRet_Val = 0, iSize = 0;

	cout<<"[SEARCHING]: File name having size greater than 10 bytes.."<<endl<<endl;

	// traverse till input file not complete
	while((iRet_Val = read(iFD_In,&stInfo,sizeof(stInfo))) > 0)
	{
		iSize = stInfo.iFileLength;

		if(iSize > MAX_BYTE)	// MAX_BYTE is the macro of '10'
		{
			cCheck = TRUE;
			cout<<iSize<<" Byte \t\t\t:"<<stInfo.cName<<endl;
		}


		lseek(iFD_In,iSize,SEEK_CUR);				// skip the "file_data" section from Input file
		memset(&stInfo,0,sizeof(stInfo));			// flush the memory
	}

	if (!cCheck)
	{
		cout<<"[SORRY]: Unable to get file name having size greater then 10 byte"<<endl;
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
	obj.GetMaxFile();	
	
	return STATUS_SUCCESS;
}
