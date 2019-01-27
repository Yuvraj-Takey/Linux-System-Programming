#include "header.h"

class Accept
{
private:
	int fd, file_mode;
	char my_File[MAXNAME];
public:
	Accept(const char *,char*);
	static short Mode_Check(char*);
	~Accept();
};

Accept::Accept(const char* file_Name, char* ARG_mode)	// parameterised
{
	strcpy(my_File,file_Name);
	
	if(strcasecmp(ARG_mode,"read") == 0)
	{
		file_mode = O_RDONLY;
	}
	else if(strcasecmp(ARG_mode,"write") == 0)
	{
		file_mode = O_WRONLY;
	}
	else if(strcasecmp(ARG_mode,"read_write") == 0)
	{
		file_mode = O_RDWR;
	}
	else if(strcasecmp(ARG_mode,"create") == 0)
	{
		file_mode = O_CREAT;
	}
	else if(strcasecmp(ARG_mode,"truncate") == 0)
	{
		file_mode = O_WRONLY | O_TRUNC;
	}
	else
	{
		cout<<"[SORRY]: File mode is not valid\nPlease refer README file"<<endl;
		cout<<"Getting file default mode [Read Mode]..."<<endl;
		file_mode = O_RDONLY;
	}


	fd = open(my_File,file_mode);
	if(fd < INVALID_FD)
	{
		// if file is not open then display error message and try to create the new file
		cout<<"[SORRY]: Unable to open the file\nReason: "<<strerror(errno)<<endl<<"Creating new file with name ["<<my_File<<"]..."<<endl;
		fd = creat(my_File,0777);
		if(fd < INVALID_FD)
		{
			cout<<"[SORRY]: Unable to create the file\nReason: "<<strerror(errno)<<endl;
		}
		else
		{
			cout<<"[DONE]: File is successfully created in "<<ARG_mode<<" mode with file descripter : "<<fd<<endl<<endl;
		}
	}
	else
	{
		cout<<"[DONE]: File is successfully opened in "<<ARG_mode<<" mode with file descripter : "<<fd<<endl<<endl;
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
		cout<<"[ERROR]: Incorrect parameters,\nyour argument count is not matched"<<endl;
		cout<<"[Usage]: <executable_name> <file_name> <file_mode>"<<endl;
		return STATUS_ERR;
	}

	//object creation
	Accept obj(argv[1],argv[2]);
	
	return STATUS_SUC;
}
