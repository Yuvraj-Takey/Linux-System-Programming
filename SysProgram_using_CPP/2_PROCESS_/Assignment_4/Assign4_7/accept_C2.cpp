#include "header.h"

class Accept
{
public:
	Accept();
	void count_Capital(const char*, const char*);
	~Accept();
};

Accept::Accept()
{
	// code for allocation memory on startup
	// which could be sharable.
}

void Accept::count_Capital(const char* cIn_File,const char* cOut_File)
{
	int in_FD = 0, out_FD = 0,iRet_Val = 0, iCount = 0;
	char cBuff_Data[MAXSIZE] = {'\0'}, cOutput_Data[50] = {'\0'};				// for data_read/write
	unsigned short sIndex = 0;												// for loop counter

	// open the Input file
	if((in_FD = open(cIn_File,O_RDONLY)) == STATUS_ERR)
	{
		cout<<"[SORRY_2]: unable to open the file"<<endl<<"Reason: "<<strerror(errno)<<endl;
		return;
	}
	else
	{
		cout<<"[CHILD_2]: "<<cIn_File<<" -file opened for Input"<<endl;
	}

	// open output file
	if((out_FD = open(cOut_File,O_WRONLY | O_APPEND)) == STATUS_ERR)
	{
		cout<<"[SORRY_2]: unable to open the file"<<endl<<"Reason: "<<strerror(errno)<<endl;
		close(in_FD);
		return;
	}
	else
	{
		cout<<"[CHILD_2]: "<<cOut_File<<" -file opened for output"<<endl;
	}	

	// read the Input file
	while((iRet_Val = read(in_FD,cBuff_Data,MAXSIZE)) != READ_END)		// READ_END is macro of 0
	{
		for(sIndex = 0; sIndex < iRet_Val; sIndex++)
		{
			if((cBuff_Data[sIndex] >= 'A') && (cBuff_Data[sIndex] <= 'Z'))
			{
				iCount++;
			}
		}

		// vanish the buffer
		memset(cBuff_Data,0,MAXSIZE);
	}

	// manage string
	sprintf(cOutput_Data,"[CHILD_2]: Number of Capital characters are->  %d",iCount);

	// Writing result into output file
	if((iRet_Val = write(out_FD,cOutput_Data,strlen(cOutput_Data))) == STATUS_ERR)
	{
		cout<<"[CHILD_2]: Unable to write into output file"<<endl<<"Reason: "<<strerror(errno)<<endl;
	}

	close(in_FD);
	close(out_FD);
}

Accept::~Accept()
{
	// code for deallocation memory
}

int main(int argc, char* argv[])
{
	cout<<"[CHILD_2] Hello, Inside Process_2"<<endl;
	
	Accept Obj;
	Obj.count_Capital("hello","count");

	cout<<"[CHILD_2] Exiting.."<<endl;
	return STATUS_SUC;
}
