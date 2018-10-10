#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

using namespace std;

#define STATUS_FAILURE		-1
#define STATUS_SUCCESS		0
#define INVALID_FD			STATUS_FAILURE
#define ARG_LIMIT 			2
#define TRUE				1
#define FALSE				0
#define MAXNAME				255
#define MAX_BYTE			10	

#pragma pack(1)
typedef struct fileInfo_stat
{
	char cName[50];
	int sPermission;
	int iFileLength;
}FILEINFO;
