/*--------------------------------------------------------------
*
* This file contain another logic of same assignment
* this is for future enhancement purpose
*
------------------------------------------------------------*/


#include "header.h"

class Accept
{
private:
	int fd;
	char my_File[MAXNAME];
public:
	char buffer[BUFFSIZE];
	Accept(const char*);
	~Accept();
	void readByte(int);
};

Accept::Accept(const char* file_Name)	// parameterised 
{
	fd = 0;
	memset(my_File,0,sizeof(my_File));
	memset(buffer,0,sizeof(buffer));

	////////////////////////////////////////////////////////////////////////////////////
	
	strcpy(my_File,file_Name);

	fd = open(my_File,O_RDONLY);
	if(fd < INVALID_FD)
	{
		// if file is not open then display error message.
		cout<<"\n[SORRY]: Unable to open the file\nError_Code : "<<errno<<endl<<"Reason: "<<strerror(errno)<<endl;
	}
	else
	{
		cout<<"[DONE]: File is successfully opend with file descripter : "<<fd<<endl;
	}
}

void Accept::readByte(int number_Bytes)
{
	if(fd < INVALID_FD)
	{
		return;
	}

	int iRet_Val = 0;
	memset(buffer,0,sizeof(buffer));
	
	while((iRet_Val = read(fd,buffer,BUFFSIZE)) != 0)
	{
		if(iRet_Val < 0)
		{
			cout<<"[SORRY]: Unable to read the file\nReason: "<<strerror(errno)<<endl;
			break;
		}
		else
		{
			if(number_Bytes > BUFFSIZE)
			{
				write(1,buffer,iRet_Val);
				number_Bytes = number_Bytes - BUFFSIZE;
			}
			else
			{
				write(1,buffer,number_Bytes);
				cout<<endl<<"End of file"<<endl;
				break;
			}
			
			// 500		<	512
			if(iRet_Val < BUFFSIZE)
			{
				cout<<endl<<"End of file"<<endl;
				break;
			}
		}
	}
}

Accept::~Accept()
{
	if(fd > INVALID_FD)
	{
		close(this->fd);
	}
}

int main(int argc, char* argv[])
{	
	if(argc != ARG_LIMIT)
	{
		cout<<"[SORRY]: Incorrect parameters,\nyour argument count is not matched"<<endl;
		cout<<"[Usage]: <executable_name> <file_name> <number_of_bytes_to_read>"<<endl;
		return STATUS_ERR;
	}

	if((atoi(argv[2])) < INVALID_BYTE)
	{
		cout<<"[SORRY]: Number of bytes to read is Incorrect"<<endl;
		return STATUS_ERR;
	}
	
	Accept obj(argv[1]);
	obj.readByte(atoi(argv[2]));	
	
	return STATUS_SUC;
}
