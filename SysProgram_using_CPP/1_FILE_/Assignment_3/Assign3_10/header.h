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
#define MAXBUFF				512
#define DIR_PERM			0777
#define FILE_PERM 			0666
#define READ				4
#define WRITE				2
#define EXECUTE				1

#pragma pack(1)
typedef struct fileInfo_stat
{
	char cName[50];
	int sPermission;
	int iFileLength;
}FILEINFO;
