#include "header.h"

class Accept
{
private:
	int fd;
	char my_File[MAXNAME];
public:
	Accept(const char*);
	~Accept();
	void writeByte();
};

Accept::Accept(const char* file_Name)	// parameterised
{
	fd = 0;
	memset(my_File,0,sizeof(my_File));

	////////////////////////////////////////////////////////////////////////////////////
	
	strcpy(my_File,file_Name);

	fd = open(my_File,O_RDWR);
	if(fd < INVALID_FD)
	{
		// if file is not open then display error message and try to create the new file
		cout<<"[SORRY]: Unable to open the file\nReason: "<<strerror(errno)<<endl<<"Creating new file..."<<endl;

		// Creating file
		fd = open(my_File,O_RDWR | O_CREAT, FILE_PERM);
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

void Accept::writeByte()
{
	if(fd < INVALID_FD)
	{
		return;
	}

	int iRet_Val = 0;
	char cDecision = '\0';
	INFO info_Stat;

	cout<<"Enter user name"<<endl;
	cin>>info_Stat.name;
	cout<<"Enter user ID"<<endl;
	cin>>info_Stat.iID_Num;
	cout<<"Enter salary"<<endl;
	cin>>info_Stat.iSalary;
	cout<<"Enter user age(real-age)"<<endl;
	cin>>info_Stat.s_Age;

	iRet_Val = write(fd,&info_Stat,sizeof(info_Stat));
	if(iRet_Val < 0)
	{
		cout<<"[SORRY]: Unable to write into the file\nReason: "<<strerror(errno)<<endl;
	}
	else
	{
		cout<<"[DONE]: Data is written successfully into given file"<<endl<<endl;

		info_Stat = (INFO){0};								// reset to default value	// vanish

		lseek(fd,0,0);

		cout<<"Do you want to read data from file (yes/no)?_ ";
		cin>>cDecision;

		if(cDecision == 'y')
		{
			iRet_Val = read(fd,&info_Stat,sizeof(info_Stat));
			if(iRet_Val < 0)
			{
				cout<<"[SORRY]: Unable to read file\nReason: "<<strerror(errno)<<endl;
			}
			else
			{
				cout<<"Name\t\t:"<<info_Stat.name<<endl;
				cout<<"ID\t\t:"<<info_Stat.iID_Num<<endl;
				cout<<"Salary\t\t:"<<info_Stat.iSalary<<endl;
				cout<<"Age\t\t:"<<info_Stat.s_Age<<endl;
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
		cout<<"[Usage]: <executable_name> <file_name>"<<endl;
		return STATUS_ERR;
	}
	
	Accept obj(argv[1]);
	obj.writeByte();	
	
	return STATUS_SUC;
}
