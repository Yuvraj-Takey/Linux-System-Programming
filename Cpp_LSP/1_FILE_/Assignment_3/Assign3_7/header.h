#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

using namespace std;

#define STATUS_ERR	-1
#define STATUS_SUC	0
#define INVALID_FD	0
#define BUFFSIZE	512
#define MAXNAME		255
#define ARG_LIMIT	2
#define FILE_PERM 	0666

#pragma pack(1)
typedef struct myinfo
{
	char name[MAXNAME];	// Name
	int iID_Num;		// ID
	int iSalary;		// salary
	short s_Age;		// Age	
}INFO;

