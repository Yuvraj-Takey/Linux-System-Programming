#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

using namespace std;

#define STATUS_ERR 		-1
#define STATUS_SUC 		0
#define INVALID_FD 		0
#define INVALID_WRITE	INVALID_FD
#define ARG_LIMIT 		3
#define MAXNAME			255
#define DIR_PERM		0777
#define FILE_PERM		0666
