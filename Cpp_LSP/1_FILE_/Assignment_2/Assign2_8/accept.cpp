#include "header.h"

class Accept
{
private:
	int fd_Open, fd_Creat;
	char exist_File[MAXNAME];
	char new_File[MAXNAME];
public:
	char buffer[BUFFSIZE];
	Accept(const char*, const char*);
	~Accept();
	void fileCopy();
};

Accept::Accept(const char* file_Name1, const char* file_Name2)	// parameterised
{
	fd_Open = 0;
	fd_Creat = 0;
	memset(exist_File,0,MAXNAME);
	memset(new_File,0,MAXNAME);
	memset(buffer,0,BUFFSIZE);

	////////////////////////////////////////////////////////////////////////////////////
	
	strcpy(exist_File,file_Name1);
	strcpy(new_File,file_Name2);

	fd_Open = open(exist_File,O_RDONLY);
	if(fd_Open < INVALID_FD)
	{
		// if file is not open then display error message.
		cout<<"\n[SORRY]: Unable to open '"<<exist_File<<"' file"<<endl<<"Reason: "<<strerror(errno)<<endl;
	}
	else
	{
		// creating new file
		fd_Creat = creat(new_File,0666 | O_WRONLY);
		if(fd_Creat < INVALID_FD)
		{
			cout<<"\n[SORRY]: Unable to create '"<<new_File<<"' file"<<endl<<"Reason: "<<strerror(errno)<<endl;
		}
	}
}

void Accept::fileCopy()
{
	int iRead_Cnt = 0, iWrite_Cnt = 0;

	if((fd_Open < INVALID_FD) || (fd_Creat < INVALID_FD))
	{
		return;
	}

	// getting the data from existing file
	while((iRead_Cnt = read(fd_Open,buffer,BUFFSIZE)) != 0)
	{
		if(iRead_Cnt < 0)
		{
			cout<<"[SORRY]: Unable to read the file\nReason: "<<strerror(errno)<<endl;
			break;
		}
		else
		{
			// writing the data from existing file into new created file
			iWrite_Cnt = write(fd_Creat,buffer,iRead_Cnt);
			
			if(iWrite_Cnt < 0)
			{
				cout<<"[SORRY]: Unable to write data into another file\nReason: "<<strerror(errno)<<endl;
				break;
			}
		}
	}

	// checking for invalid termination of while loop
	if((iRead_Cnt < 0) || (iWrite_Cnt < 0))
	{
		cout<<"[SORRY]: Fail to copy data"<<endl;
	}
	else
	{
		cout<<"[DONE]: Your data is successfully copied into given file"<<endl;
	}
}

Accept::~Accept()
{
	if(fd_Open > INVALID_FD)
	{
		close(this->fd_Open);
	}
	else if (fd_Creat > INVALID_FD)
	{
		close(this->fd_Creat);
	}
}

int main(int argc, char* argv[])
{	
	if(argc != ARG_LIMIT)
	{
		cout<<"[SORRY]: Incorrect parameters,\nyour argument count is not matched"<<endl;
		cout<<"[Usage]: <executable_name> <file_name1> <file_name2>"<<endl;
		return STATUS_ERR;
	}
	
	Accept obj(argv[1],argv[2]);
	obj.fileCopy();	
	
	return STATUS_SUC;
}
