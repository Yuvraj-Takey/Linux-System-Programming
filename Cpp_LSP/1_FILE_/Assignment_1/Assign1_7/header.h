#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

using namespace std;

#define STATUS_ERR	-1
#define STATUS_SUC	0
#define INVALID_FD	0
#define BUFFSIZE	1024
#define MAXNAME		255
#define ARG_LIMIT	2

