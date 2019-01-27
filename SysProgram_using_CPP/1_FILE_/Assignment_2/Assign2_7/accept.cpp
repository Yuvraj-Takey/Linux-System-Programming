#include "header.h"
#include <stdio.h>

class Accept
{
private:
	DIR *dir;
	char my_Dir[MAXNAME];
public:	
	struct stat fileInfo;
	Accept(const char*);
	~Accept();
	void largest_REG();
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

void Accept::largest_REG()
{
	if(dir == NULL)
	{
		return;
	}

	struct dirent* Dir_Read;
	int iMax_Size = (STATUS_ERR);
	char cMax_File[MAXNAME] = {'\0'},cPath_Name[255] = {'\0'};
	
	cout<<"Searching.."<<endl;
	while((Dir_Read = readdir(dir)) != NULL)
	{
		sprintf(cPath_Name,"%s/%s",my_Dir,Dir_Read->d_name);
		stat(cPath_Name,&fileInfo);
		
		if(S_ISREG(fileInfo.st_mode))
		{	
			if(iMax_Size < (int)fileInfo.st_size)
			{
				memset(cMax_File,0,MAXNAME);
				strcpy(cMax_File,Dir_Read->d_name);
				iMax_Size = (int)fileInfo.st_size;		
			}
		}
		memset(&fileInfo,0,sizeof(fileInfo));
	}

	if (iMax_Size != STATUS_ERR)
	{
		cout<<"[DONE]: '"<<cMax_File<<"' is the largest regular file in "<<my_Dir<<" directory with length "<<iMax_Size<<" KB"<<endl<<endl;
	}
	else
	{
		cout<<"[SORRY]: No regular file found here"<<endl;
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
	obj.largest_REG();	
	
	return STATUS_SUC;
}

	/*struct dirent {
               ino_t          d_ino;       // inode number
               off_t          d_off;       // not an offset; see NOTES 
               unsigned short d_reclen;    // length of this record 
               unsigned char  d_type;      // type of file; not supported
                                           //   by all filesystem types 
               char           d_name[256]; // filename 
           };*/

		/*	predefine structure :
		struct stat {
               dev_t     st_dev;         // ID of device containing file 
               ino_t     st_ino;         // inode number 
               mode_t    st_mode;        // protection 
               nlink_t   st_nlink;       // number of hard links 
               uid_t     st_uid;         // user ID of owner 
               gid_t     st_gid;         // group ID of owner 
               dev_t     st_rdev;        // device ID (if special file) 
               off_t     st_size;        // total size, in bytes 
               blksize_t st_blksize;     // blocksize for filesystem I/O 
               blkcnt_t  st_blocks;      // number of 512B blocks allocated
               ...
               ...
               }
		*/