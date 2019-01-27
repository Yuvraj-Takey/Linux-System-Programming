#include "header.h"

class Accept
{
private:
	DIR *dir;
	char my_Dir[MAXNAME];
public:	
	Accept(const char*);
	~Accept();
	void ls_Dir();
};

Accept::Accept(const char* dir_Name)	// parameterised
{
	strcpy(my_Dir,dir_Name);

	dir = opendir(my_Dir);
	if(dir == NULL)
	{
		cout<<"[SORRY]: Unable to open directory\nReason: "<<strerror(errno)<<endl;
	}
	else
	{
		cout<<"[DONE]: Directory is successfully opened"<<endl;
	}
}

void Accept::ls_Dir()
{
	if(dir == NULL)
	{
		return;
	}

	struct dirent* Dir_Read;
	
	while((Dir_Read = readdir(dir)) != NULL)
	{
		/*struct dirent {
               ino_t          d_ino;       // inode number
               off_t          d_off;       // not an offset; see NOTES 
               unsigned short d_reclen;    // length of this record 
               unsigned char  d_type;      // type of file; not supported
                                           //   by all filesystem types 
               char           d_name[256]; // filename 
           };*/

		if(Dir_Read->d_type == DT_BLK)
		{
			cout<<"\t\tBlock-device file"<<Dir_Read->d_name<<endl;
		}
		else if(Dir_Read->d_type == DT_CHR)
		{
			cout<<"Char-device file\t\t"<<Dir_Read->d_name<<endl;
		}
		else if(Dir_Read->d_type == DT_DIR)
		{
			cout<<"Directory file\t\t"<<Dir_Read->d_name<<endl;
		}
		else if(Dir_Read->d_type == DT_FIFO)
		{
			cout<<"Pipe file(named)\t\t"<<Dir_Read->d_name<<endl;
		}
		else if(Dir_Read->d_type == DT_LNK)
		{
			cout<<"Sym-link file\t\t"<<Dir_Read->d_name<<endl;
		}
		else if(Dir_Read->d_type == DT_REG)
		{
			cout<<"Regular file\t\t"<<Dir_Read->d_name<<endl;
		}
		else if(Dir_Read->d_type == DT_SOCK)
		{
			cout<<"Socket file\t\t"<<Dir_Read->d_name<<endl;
		}
		else
		{
			cout<<"Unknown file\t\t"<<Dir_Read->d_name<<endl;
		}
	}
}

Accept::~Accept()
{
	if(dir != NULL)
	{
		closedir(this->dir);
	}
}

int main(int argc, char* argv[])
{	
	if(argc != ARG_LIMIT)
	{
		cout<<"[ERROR]: Incorrect parameters,\nyour argument count is not matched"<<endl;
		cout<<"[Usage]: <executable_name> <dir_name>"<<endl;
		return STATUS_ERR;
	}
	
	Accept obj(argv[1]);
	obj.ls_Dir();	
	
	return STATUS_SUC;
}
