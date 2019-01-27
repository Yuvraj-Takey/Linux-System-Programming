#include "header.h"

class Accept
{
private:
	int fd;
	char my_File[MAXNAME];
public:
	struct stat fileInfo;		
	Accept(const char*);
	void GetFileInfo();
	~Accept();
	
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
		// if file is not open then display error message.
		cout<<"\n[SORRY]: Unable to open the file\nError_Code : "<<errno<<endl<<"Reason: "<<strerror(errno)<<endl;
	}
}

void Accept::GetFileInfo()
{

	if(fd < INVALID_FD)
	{
		return ;
	}

	if(fstat(fd,&fileInfo) == STATUS_ERR)		// similar functions are => stat() and lstat()
	{
		perror("stat");
		return ;
	}

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

	cout<<"User ID  \t\t:"<<fileInfo.st_uid<<endl;
	cout<<"Group ID \t\t:"<<fileInfo.st_gid<<endl;
	cout<<"File Size  \t\t:"<<fileInfo.st_size<<" bytes"<<endl;

	cout<<"Number of Links  \t:"<<fileInfo.st_nlink<<endl;
	cout<<"File inode number \t:"<<fileInfo.st_ino<<endl;
	cout<<"File system number \t:"<<fileInfo.st_dev<<endl;
	cout<<"blocks allocated number\t:"<<fileInfo.st_blocks<<endl;
	 
	cout<<"File Permissions \t:(";
	(S_ISDIR(fileInfo.st_mode)) ? cout<<"d" : cout<<"-";
	(fileInfo.st_mode & S_IRUSR) ? cout<<"r" : cout<<"-";
	(fileInfo.st_mode & S_IWUSR) ? cout<<"w" : cout<<"-";
	(fileInfo.st_mode & S_IXUSR) ? cout<<"x" : cout<<"-";
	(fileInfo.st_mode & S_IRGRP) ? cout<<"r" : cout<<"-";
	(fileInfo.st_mode & S_IWGRP) ? cout<<"w" : cout<<"-";
	(fileInfo.st_mode & S_IXGRP) ? cout<<"x" : cout<<"-";
	(fileInfo.st_mode & S_IROTH) ? cout<<"r" : cout<<"-";
	(fileInfo.st_mode & S_IWOTH) ? cout<<"w" : cout<<"-";
	(fileInfo.st_mode & S_IXOTH) ? cout<<"x" : cout<<"-";
	cout<<")"<<endl;
	 
	if(S_ISLNK(fileInfo.st_mode))
	{
		cout<<"It is symbolic link"<<endl;
	}
	else if(S_ISREG(fileInfo.st_mode))
	{
		cout<<"It is regular file"<<endl;	
	}
	else if(S_ISDIR(fileInfo.st_mode))
	{
		cout<<"It is directory file"<<endl;	
	}

	cout<<"Last access: "<<ctime(&fileInfo.st_atime);
	cout<<"Last modify: "<<ctime(&fileInfo.st_mtime);
	cout<<"Last status: "<<ctime(&fileInfo.st_ctime);
     
     

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
	obj.GetFileInfo();	
	
	return STATUS_SUC;
}
