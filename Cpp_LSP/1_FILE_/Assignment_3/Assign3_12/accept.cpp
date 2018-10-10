#include "header.h"

class Accept
{
private:
	int iFD;
	char my_File[MAXNAME];
public:
	Accept(const char *);
	void Hole_In_File();
	~Accept();
};

Accept::Accept(const char* file_Name)
{
	strcpy(my_File,file_Name);

	iFD = open(my_File,O_WRONLY);
	if(iFD < INVALID_FD)
	{
		// if file is not open then display error message and try to create the new file
		cout<<"[SORRY]: Unable to open the file\nReason: "<<strerror(errno)<<endl<<"Creating new file..."<<endl;
		iFD = creat(my_File,FILE_PERM);
		if(iFD < INVALID_FD)
		{
			cout<<"[SORRY]: Unable to create the file\nReason: "<<strerror(errno)<<endl;
		}
		else
		{
			cout<<"[DONE]: File is successfully created"<<endl;
		}
	}
	else
	{
		cout<<"[DONE]: File is successfully opened"<<endl;
	}
}

void Accept::Hole_In_File()
{
	int iRet_Val = 0;

	if((iRet_Val = lseek(iFD,HOLE_SIZE,SEEK_END)) == STATUS_ERR)
	{
		cout<<"[SORRY]: Unable to seek in the file"<<endl;
		return ;
	}

	if((iRet_Val = write(iFD,"*",BYTE)) <= INVALID_WRITE)
	{
		cout<<"[SORRY]: Unable to create Hole in file"<<endl;
	}
	else
	{
		cout<<"[DONE]: successfully created Hole in file"<<endl;
	}

}

Accept::~Accept()
{
	if(iFD > INVALID_FD)
	{
		close(this->iFD);
	}
}

int main(int argc, char* argv[])
{	
	if(argc != ARG_LIMIT)
	{
		cout<<"[ERROR]: Incorrect parameters,\nyour argument count is not matched"<<endl;
		cout<<"[Usage]: <executable_name> <file_name>"<<endl;
		return STATUS_ERR;
	}
	
	Accept obj(argv[1]);
	obj.Hole_In_File();	
	
	return STATUS_SUC;
}
