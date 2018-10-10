#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

using namespace std;

#define STATUS_ERR 		-1
#define STATUS_SUC 		0
#define INVALID_FD 		0
#define INVALID_WRITE	INVALID_FD
#define ARG_LIMIT 		2
#define MAXNAME			255
#define FILE_PERM		0666
#define BYTE			1
#define HOLE_SIZE		1024
