#include "header.h"

class Accept
{
private:
	int iFD;
	char cMy_File[MAXNAME];
public:
	Accept(const char*);
	void desktop_Stat();
	~Accept();
};

Accept::Accept(const char* cFile_Name)
{
	memset(cMy_File,0,MAXNAME);
	memcpy(cMy_File,cFile_Name,strlen(cFile_Name));

	// create new file
	if((iFD = creat(cMy_File,FILE_PERM)) == STATUS_ERR)
	{
		cout<<"[SORRY]: unable to create the file"<<endl<<"Reason: "<<strerror(errno)<<endl;
	}
	else
	{
		cout<<"[-CHILD]: "<<cMy_File<<" -file successfully created"<<endl;
	}
}

void Accept::desktop_Stat()
{
	if(iFD == STATUS_ERR)
	{
		return;
	}
	
	DIR *stDir;
	short sRet_Val = 0;
	struct dirent *stD_Read;
	char cPath_Name[MAXNAME] = {'\0'}, cBuffer[MAXFILE] = {'\0'};
	struct passwd* stPasswd;

	/*	This structure contain basic information about current Login user
	*
	*	struct passwd {
    *        char   *pw_name;       // username 
    *        char   *pw_passwd;     // user password 
    *        uid_t   pw_uid;        // user ID 
    *        gid_t   pw_gid;        // group ID 
    *        char   *pw_gecos;      // user information
    *        char   *pw_dir;        // home directory 
    *        char   *pw_shell;      // shell program 
    *       };
	*/

	// fill the "passwd" structure  
	stPasswd = getpwuid(getuid());

	// copy the home directory string and make full path
	memcpy(cPath_Name,stPasswd->pw_dir,strlen(stPasswd->pw_dir));
	strcat(cPath_Name,"/Desktop");

	// open the Desktop directory
	if((stDir = opendir(cPath_Name)) == NULL)
	{
		cout<<"[SORRY]: unable to open the '"<<cPath_Name<<"' directory\nReason: "<<strerror(errno)<<endl;
		return;
	}

	// read Desktop directory
	while((stD_Read = readdir(stDir)) != NULL)
	{
		// ignore "current" and "Parent" directory
		if(((strcmp(stD_Read->d_name,".")) != 0) && ((strcmp(stD_Read->d_name,"..")) != 0))
		{
			strcat(stD_Read->d_name,"\n");

			// write the name of file into 'output' file
			if((sRet_Val = write(iFD,(stD_Read->d_name),(unsigned short)strlen(stD_Read->d_name))) == STATUS_ERR)
			{
				cout<<"[SORRY]: unable to perform write operation\nReason: "<<strerror(errno)<<endl;
				break;
			}
		}
	}

	cout<<"[-CHILD]: Task Completed"<<endl;
}

Accept::~Accept()
{
	if(iFD != STATUS_ERR)
	{
		close(iFD);
	}
}

int main(int argc, char* argv[])
{
	cout<<"[-CHILD]: My PID is- "<<getpid()<<endl;

	Accept Obj("demo");
	Obj.desktop_Stat();

	cout<<"[-CHILD]---Exiting---"<<endl;
	return STATUS_SUC;
}
