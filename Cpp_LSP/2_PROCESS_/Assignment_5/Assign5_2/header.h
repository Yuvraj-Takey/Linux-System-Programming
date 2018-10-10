#include <iostream>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
using namespace std;

#define STATUS_ERR -1
#define STATUS_SUC 0