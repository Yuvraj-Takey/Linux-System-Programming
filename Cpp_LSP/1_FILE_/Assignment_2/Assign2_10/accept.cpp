#include "header.h"

class Accept
{
private:
	DIR *S_Dir;
	DIR *D_Dir;
	int iD_Dir;
	char Src_Name[MAXNAME], Dest_Name[MAXNAME];
public:	
	Accept(const char*, const char*);
	~Accept();
	void Move_Files();
};

Accept::Accept(const char* dir_Name1, const char* dir_Name2)
{
	memset(Src_Name,0,MAXNAME);
	memset(Dest_Name,0,MAXNAME);

	//////////////////////////////////////////////////////////////////

	strcpy(Src_Name,dir_Name1);
	strcpy(Dest_Name,dir_Name2);

	S_Dir = opendir(Src_Name);
	if(S_Dir == NULL)
	{
		cout<<"[SORRY]: Unable to open '"<<Src_Name<<"' directory\nReason: "<<strerror(errno)<<endl;
	}
	else
	{
		if((D_Dir = opendir(Dest_Name)) == NULL)
		{
			if((iD_Dir = mkdir(Dest_Name, 0777)) == STATUS_ERR)
			{
				cout<<"[SORRY]: Unable to create '"<<Dest_Name<<"' directory"<<endl<<"Reason: "<<strerror(errno)<<endl;
			}
			else
			{		
				close(iD_Dir);					// mkdir return integer value
				D_Dir = opendir(Dest_Name);
			}

		}
		else
		{
			cout<<"[DONE]: Successfully opened directories"<<endl;
		}
	}
}

void Accept::Move_Files()
{
	if((S_Dir == NULL) || (D_Dir == NULL))
	{
		return;
	}

	bool bRead_Invalid = false, bComplete = false;
	short Src_fd = 0,Dest_fd = 0;
	short sRead_Cnt = 0, sWrite_Cnt;
	struct dirent* Dir_Read;
	char cNew_File[MAXNAME] = {'\0'};
	char cNew_Path[MAXNAME] = {'\0'}, cOld_Path[MAXNAME] = {'\0'};
	char cBuffer[MAXBUFF] = {'\0'};
	
	while((Dir_Read = readdir(S_Dir)) != NULL)							// open source directory
	{
		if( ((strcmp(Dir_Read->d_name,".")) != 0) && ((strcmp(Dir_Read->d_name,"..")) != 0) )
		{
			memset(cOld_Path,0,MAXNAME);
			memset(cNew_File,0,MAXNAME);
			memset(cNew_Path,0,MAXNAME);
			memset(cBuffer,0,MAXBUFF);

			sprintf(cOld_Path,"%s/%s",Src_Name,Dir_Read->d_name);			// make path

			if((Src_fd = open(cOld_Path, O_RDONLY)) >= STATUS_SUC)
			{
				sprintf(cNew_Path,"%s/%s",Dest_Name,Dir_Read->d_name);

				if((Dest_fd = creat(cNew_Path,0777)) >= STATUS_SUC)
				{
					while((sRead_Cnt = read(Src_fd,cBuffer,MAXBUFF)) != 0)
					{
						if(sRead_Cnt < STATUS_SUC)
						{
							bRead_Invalid = true;
							cout<<"[SORRY]: Unable to read '"<<cOld_Path<<"' file\nReason: "<<strerror(errno)<<endl;
							break;
						}
						else
						{
							sWrite_Cnt = write(Dest_fd,cBuffer,sRead_Cnt);
				
							if(sWrite_Cnt < 0)
							{
								bRead_Invalid = true;
								cout<<"[SORRY]: Unable to write in '"<<cNew_File<<"' file\nReason: "<<strerror(errno)<<endl;
								break;
							}
							else
							{
								bComplete = true;
							}
						}
					}

					// if file2 gets created, but due to some reason file1 could not be read, (remove file2)
					if(bRead_Invalid == true)
					{
						unlink(cNew_Path);
					}
					else if(bComplete == true)
					{
						unlink(cOld_Path);
					}
				}
				else
				{
					cout<<"[SORRY]: Can't move '"<<cNew_File<<"'.."<<endl<<"Reason: "<<strerror(errno)<<endl;
				}
			}
			else
			{
				cout<<"[SORRY]: Unable to open '"<<cOld_Path<<"' from source directory"<<endl<<"Reason: "<<strerror(errno)<<endl;
			}
		}
	}
	if(bComplete)
		cout<<"[DONE]: operation completed"<<endl;
	else
		cout<<"[SORRY]: operation not completed"<<endl;
}

Accept::~Accept()
{
	if(S_Dir != NULL)
	{
		closedir(this->S_Dir);
	}
	else if(D_Dir != NULL)
	{
		closedir(this->D_Dir);
	}
}

int main(int argc, char* argv[])
{	
	if(argc != ARG_LIMIT)
	{
		cout<<"[ERROR]: Incorrect parameters,\nyour argument count is not matched"<<endl;
		cout<<"[Usage]: <executable_name> <dir_name1> <dir_name2>"<<endl;
		return STATUS_ERR;
	}
	
	Accept obj(argv[1] ,argv[2]);
	obj.Move_Files();	
	
	return STATUS_SUC;
}


