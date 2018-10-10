#include "header.h"

class Accept
{
private:
	int fd;
	char my_File[MAXNAME];
public:
	Accept(const char*);
	~Accept();
	void readByte();
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
		// if file is not open then display error message and try to create the new file
		cout<<"[SORRY]: Unable to open the file\nReason: "<<strerror(errno)<<endl;
	}
	else
	{
		cout<<"[DONE]: File is successfully opened with file descripter : "<<fd<<endl;
	}
}

void Accept::readByte()
{
	if(fd < INVALID_FD)
	{
		return;
	}

	int iRet_Val = 0;
	INFO info_Stat;
	
	while((iRet_Val = read(fd,&info_Stat,sizeof(info_Stat))) != STATUS_SUC)
	{
		if(iRet_Val == 0)
		{
			cout<<"[SORRY]: Unable to read file\nReason: "<<strerror(errno)<<endl;
		}
		else
		{

			cout<<"Name		:"<<info_Stat.name<<endl;
			cout<<"ID		:"<<info_Stat.iID_Num<<endl;
			cout<<"Salary		:"<<info_Stat.iSalary<<endl;
			cout<<"Age 		:"<<info_Stat.s_Age<<endl<<endl;
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
