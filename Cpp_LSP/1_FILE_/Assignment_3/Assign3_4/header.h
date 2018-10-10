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
#define INVALID_FD			STATUS_SUCCESS
#define ARG_LIMIT 			2
#define MAXNAME				255
#define MAXBUFF				10
#define FILE_PERM 			0666

