#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

using namespace std;

#define TRUE			1
#define FALSE			0
#define STATUS_ERR		(-1)
#define STATUS_SUC		0
#define INVALID_FD		FALSE
#define INVALID_BYTE	FALSE
#define BUFFSIZE		20
#define MAXNAME			255
#define ARG_LIMIT 		3

