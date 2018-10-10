#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
using namespace std;

#define STATUS_ERR 		-1
#define STATUS_SUC 		0
#define MAXNAME			255
#define MAXFILE			512
#define FILE_PERM		0666