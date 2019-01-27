#include "header.h"

class Accept
{
private:
	int fd;
	char my_File[MAXNAME];
	
public:
	int iRet_Val;			// shareable memory
	Accept(const char*);
	~Accept();
	void writeByte(char*);
};

Accept::Accept(const char* file_Name)	// parameterised
{
	iRet_Val = 0;
	fd = 0;
	memset(my_File,0,sizeof(my_File));

	////////////////////////////////////////////////////////////////////////////////////
	
	strcpy(my_File,file_Name);

	fd = open(my_File,O_WRONLY);
	if(fd < INVALID_FD)
	{
		// if file is not open then display error message and try to create the new file
		cout<<"[SORRY]: Unable to open the file\nReason: "<<strerror(errno)<<endl<<"Creating new file..."<<endl;

		// Creating file
		fd = creat(my_File,0777);
		if(fd < INVALID_FD)
		{
			cout<<"[SORRY]: Unable to create the file\nReason: "<<strerror(errno)<<endl;
		}
		else
		{
			cout<<"[DONE]: File is successfully created with file descripter : "<<fd<<endl;
		}
	}
	else
	{
		cout<<"[DONE]: File is successfully opened with file descripter : "<<fd<<endl;
	}
}

void Accept::writeByte(char* buffer)
{
	if(fd < INVALID_FD)
	{
		return;
	}

	iRet_Val = write(fd,buffer,strlen(buffer));
	if(iRet_Val < 0)
	{
		cout<<"[SORRY]: Unable to write into the file\nReason: "<<strerror(errno)<<endl;
	}
	else
	{
		cout<<"[DONE]: Data is written successfully into given file"<<endl;
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
		cout<<"[Usage]: <executable_name> <file_name> <data_string>"<<endl;
		return STATUS_ERR;
	}
	
	Accept obj(argv[1]);
	obj.writeByte(argv[2]);	
	
	return STATUS_SUC;
}
