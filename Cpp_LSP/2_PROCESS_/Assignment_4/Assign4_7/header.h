#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

#define STATUS_ERR 		-1
#define STATUS_SUC 		0
#define READ_END		STATUS_SUC
#define MAXSIZE			512
#define OUTPUT_CONTENT	50