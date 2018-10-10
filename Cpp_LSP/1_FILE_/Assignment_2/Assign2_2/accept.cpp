#include "header.h"

class Accept
{
private:
	int file_mode;
	char my_File[MAXNAME];
public:
	Accept(const char *,char*);
};

Accept::Accept(const char* file_Name, char* ARG_perm)	// parameterised
{
	strcpy(my_File,file_Name);
	file_mode = -1;
	
	if(strcasecmp(ARG_perm,"read") == 0)
	{
		file_mode = R_OK;
	}
	else if(strcasecmp(ARG_perm,"write") == 0)
	{
		file_mode = W_OK;
	}
	else if(strcasecmp(ARG_perm,"execute") == 0)
	{
		file_mode = X_OK;
	}
	else
	{
		cout<<"[SORRY]: File mode is not valid\nPlease refer README file"<<endl;
	}

	if(access(my_File,file_mode) < STATUS_SUC)
	{
		cout<<"[SORRY]: "<<my_File<<" -Permission denied\nCould not has "<<ARG_perm<<" permission for this file"<<endl<<endl;
	}
	else
	{
		cout<<"[DONE]: "<<my_File<<" has "<<ARG_perm<<" permission"<<endl<<endl;
	}
	
}

int main(int argc, char* argv[])
{	
	if(argc != ARG_LIMIT)
	{
		cout<<"[ERROR]: Incorrect parameters,\nyour argument count is not matched"<<endl;
		cout<<"[Usage]: <executable_name> <file_name> <file_permission>"<<endl;
		return STATUS_ERR;
	}

	if((access(argv[1],F_OK)) != STATUS_SUC)
	{
		cout<<"[SORRY]: Given file is not present in "<<get_current_dir_name()<<endl;
		return STATUS_ERR;
	}

	//object creation
	Accept obj(argv[1],argv[2]);
	
	return STATUS_SUC;
}
