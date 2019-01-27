#include "header.h"

class Accept
{
private:
	char my_File[MAXNAME];
	
public:
	Accept(const char*);
	~Accept();
	void trunc_From_Offset(int);
};

Accept::Accept(const char* file_Name)
{
	memset(my_File,0,MAXNAME);
	memcpy(my_File,file_Name,strlen(file_Name));
}

void Accept::trunc_From_Offset(int iOffset)
{
	short iRet_Val = 0;

	if((iRet_Val = truncate(my_File,iOffset)) == STATUS_ERR)
	{
		cout<<"[SORRY]: Unable to truncate the file"<<endl<<"Reason: "<<strerror(errno)<<endl;
	}
	else
	{
		cout<<"[DONE]: successfully truncated the file"<<endl;
	}

}

Accept::~Accept()
{
	// release code_part //
}
 
int main(int argc, char* argv[])
{	
	if(argc != ARG_LIMIT)
	{
		cout<<"[SORRY]: Incorrect parameters,\nyour argument count is not matched"<<endl;
		cout<<"[Usage]: <executable_name> <file_name> <file_offset>"<<endl;
		return STATUS_ERR;
	}
	
	Accept obj(argv[1]);
	obj.trunc_From_Offset(atoi(argv[2]));	
	
	return STATUS_SUC;
}
