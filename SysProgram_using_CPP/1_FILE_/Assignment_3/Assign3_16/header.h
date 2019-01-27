#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

using namespace std;

#define STATUS_ERR 		-1
#define STATUS_SUC 		0
#define INVALID_FD 		STATUS_ERR
#define INVALID_WRITE	0
#define ARG_LIMIT 		2
#define MAXNAME			255
#define HOLE_SIZE		1024
#define BYTE			1
#define FILE_SIZE_LIMIT	1024