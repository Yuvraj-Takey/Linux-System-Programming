#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
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
#define MAXBUFF				10
#define FILE_PERM 			0777

#pragma pack(1)
typedef struct fileInfo_stat
{
	char cName[50];
	int iInode;
	int iSize;
	short sUID;					// range 32767
	short sGID;					//		 32767
	short sHardLink;			//		 32767
}FILEINFO;