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
	void readByte();
};

Accept::Accept(const char* file_Name)	// parameterised
{
	fd = 0;
	memset(my_File,0,MAXNAME);
	memset(buffer,0,BUFFSIZE);

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

void Accept::readByte()
{
	int iRet_Val = 0;

	if(fd < INVALID_FD)
	{
		return;
	}

	while((iRet_Val = read(fd,buffer,BUFFSIZE)) != 0)
	{
		if(iRet_Val < 0)
		{
			cout<<"SORRY: Unable to read the file\nReason: "<<strerror(errno)<<endl;
			break;
		}
		else
		{
			write(1,buffer,iRet_Val);
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
		cout<<"[Usage]: <executable_name> <file_name>"<<endl;
		return STATUS_ERR;
	}
	
	Accept obj(argv[1]);
	obj.readByte();	
	
	return STATUS_SUC;
}
