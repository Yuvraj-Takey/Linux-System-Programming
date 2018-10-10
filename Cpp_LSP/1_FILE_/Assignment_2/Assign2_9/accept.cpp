#include "header.h"

class Accept
{
private:
	DIR *dir;
	char my_Dir[MAXNAME];
	char my_File[MAXNAME];
public:	
	Accept(const char*);
	~Accept();
	void ls_Dir(const char*);
};

Accept::Accept(const char* dir_Name)
{
	memset(my_File,0,MAXNAME);
	strcpy(my_Dir,dir_Name);

	dir = opendir(my_Dir);
	if(dir == NULL)
	{
		cout<<"[SORRY]: Unable to open '"<<my_Dir<<"' directory\nReason: "<<strerror(errno)<<endl;
	}
	else
	{
		cout<<"[DONE]: Directory is successfully opened"<<endl;
	}
}

void Accept::ls_Dir(const char* file_Name)
{
	if(dir == NULL)
	{
		return;
	}

	bool bCheck_Status = false;
	memcpy(my_File,file_Name,strlen(file_Name));
	struct dirent* Dir_Read;
	
	// traverse the directory till end
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

		if(memcmp(my_File,Dir_Read->d_name,strlen(Dir_Read->d_name)) == STATUS_SUC)
		{
			// set the flag for file found in given directory
			bCheck_Status = true;			
			break;
		}
	}

	if(bCheck_Status == true)
	{
		cout<<"[DONE]: "<<Dir_Read->d_name<<": file is present in '"<<my_Dir<<"' directory"<<endl;
	}
	else
	{
		cout<<"[SORRY]: Unable to locate '"<<my_File<<"' file in '"<<my_Dir<<"' directory"<<endl;
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
		cout<<"[Usage]: <executable_name> <dir_name> <file_name>"<<endl;
		return STATUS_ERR;
	}
	
	Accept obj(argv[1]);
	obj.ls_Dir(argv[2]);	
	
	return STATUS_SUC;
}
