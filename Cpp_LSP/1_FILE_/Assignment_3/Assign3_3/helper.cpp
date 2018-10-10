#include "header.h"

Accept::Accept(const char* file_Name1, const char* file_Name2)
{ 
	iS_fd = 0;
	iD_fd = 0;
	memset(cS_file,0,MAXNAME);
	memset(cD_file,0,MAXNAME);

	
	//////////////////////////////////////////////////////////////////////
	
	strcpy(cS_file,file_Name1);
	strcpy(cD_file,file_Name2);

	iS_fd = open(cS_file,O_RDONLY);
	if(iS_fd < INVALID_FD)
	{
		cout<<"[SORRY]: Unable to open '"<<cS_file<<"' file"<<endl<<"Reason: "<<strerror(errno)<<endl;
	}
	else
	{
		// creating new file
		iD_fd = open(cD_file,O_RDONLY);
		if(iD_fd < INVALID_FD)
		{
			cout<<"\n[SORRY]: Unable to open '"<<cD_file<<"' file"<<endl<<"Reason: "<<strerror(errno)<<endl;
		}
	}	
}

bool Accept::CheckEqual()
{
	bool flag = NOT_MATCH;
	int iRet1 = 0, iRet2 = 0, iIndex = 0;
	char buffer1[BUFFSIZE] = {'\0'}, buffer2[BUFFSIZE] = {'\0'};

	

	// read data from both files
	while(((iRet1 = read(iS_fd, buffer1, sizeof(buffer1))) != STATUS_SUCCESS) && ((iRet2 = read(iD_fd, buffer2, sizeof(buffer2))) != STATUS_SUCCESS))
	{
		if(iRet1 != iRet2)
		{
			flag = NOT_MATCH;
			break;
		}
		else
		{
			// compare byte wise data
			for(iIndex = 0; iIndex < iRet1; iIndex++)
			{
				if(buffer1[iIndex] != buffer2[iIndex])
				{
					flag = NOT_MATCH;
					break;
				}
				else
				{
					flag = MATCH;
				}
			}
		}
	}

	return flag;
}

Accept::~Accept()
{
	if(iS_fd > INVALID_FD) 
	{
		close(this->iS_fd);
	}
	else if (iD_fd > INVALID_FD)
	{
		close(this->iD_fd);
	}
}