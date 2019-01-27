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


		cout<<Dir_Read->d_ino<<"\t"<<Dir_Read->d_name<<endl;
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
