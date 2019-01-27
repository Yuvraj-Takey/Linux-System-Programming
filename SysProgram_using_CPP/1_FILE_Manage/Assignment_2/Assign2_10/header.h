#include <iostream>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

using namespace std;

#define STATUS_ERR -1
#define STATUS_SUC 0
#define INVALID_FD 0
#define ARG_LIMIT 3
#define MAXNAME	255
#define MAXBUFF	1024

