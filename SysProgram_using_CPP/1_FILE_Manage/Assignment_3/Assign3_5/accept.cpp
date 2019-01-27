#include "header.h"

class Accept
{
private:
	int fd;
	char my_File[MAXNAME];
public:
	Accept(const char*);
	~Accept();
	void readByte(int);
};

Accept::Accept(const char* file_Name)	// parameterised 
{
	fd = 0;
	memset(my_File,0,sizeof(my_File));
	
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
		cout<<"[DONE]: File is successfully opened with file descripter : "<<fd<<endl;
	}
}

void Accept::readByte(int read_Offset)
{
	if(fd < INVALID_FD)
	{
		return;
	}

	int iRet_Val = 0;
	char data[BUFFSIZE] = {'\0'};
	

	lseek(fd,read_Offset,SEEK_SET);
	
	if((iRet_Val = read(fd,data,BUFFSIZE)) != 0)
	{
		if(iRet_Val < 0)
		{
			cout<<"[SORRY]: Unable to read the file\nReason: "<<strerror(errno)<<endl;
		}
		else
		{
			write(1,data,iRet_Val);
			cout<<endl;
			if(iRet_Val != BUFFSIZE)
			{
				cout<<"File End !!\n*file contain less data as compare to expected amount of data*"<<endl;
			}

		}
	}
	else
	{
		cout<<"[SORRY]: Unable to read data from "<<read_Offset<<" offset\nReason: limit may exceed"<<endl;
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
		cout<<"[Usage]: <executable_name> <file_name> <file_offset>"<<endl;
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
